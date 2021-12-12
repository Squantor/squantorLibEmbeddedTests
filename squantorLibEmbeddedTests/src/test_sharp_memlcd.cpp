/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
#include <MinUnit.h>
#include <sharp_memlcd.hpp>
#include <array.hpp>


namespace {

    constexpr int maxTransferLength = 32;

    typedef struct 
    {
        int transferCount;
        int transferLength;
        uint16_t transfer[maxTransferLength];
    } stubTransferType;

    stubTransferType transfers;

    static void stubTransferReset(minunitState *) 
    {
        transfers.transferCount = 0;
        transfers.transferLength = 0;
    }

    static void stubTransfer(uint16_t * begin, uint16_t * end)
    {
        transfers.transferCount++;
        transfers.transferLength = end - begin;
        uint16_t *p = begin;
        int i = 0;
        while((p < end) && (i < maxTransferLength))
        {
            transfers.transfer[i] = *p;
            p++; i++;
        }
    }

    using lcdTestConfig = util::lcdConfig<32,32, 8>;
    util::sharpMemLcd<lcdTestConfig> testDevice;

};

static void testSharpMemLcdSetup(minunitState *) 
{
    transfers.transferCount = 0;
    transfers.transferLength = 0;
    testDevice.init();
    testDevice.setBuffer(0x0000);
}

static void testSharpMemLcdTeardown(minunitState *) 
{

}

MINUNIT_ADD(testSharpMemLcdInit, testSharpMemLcdSetup, testSharpMemLcdTeardown) 
{
    minUnitCheck(testDevice.frameBuffer[0] == 0x0101);
    minUnitCheck(testDevice.frameBuffer[3] == 0x0201);
}

MINUNIT_ADD(testSharpMemLcdPutPixel, testSharpMemLcdSetup, testSharpMemLcdTeardown) 
{
    testDevice.putPixel(0,0,1);
    testDevice.putPixel(1,1,1);
    testDevice.putPixel(18,1,1);
    testDevice.putPixel(16,1,1);
    minUnitCheck(testDevice.frameBuffer[1] == 0x0001);
    minUnitCheck(testDevice.frameBuffer[4] == 0x0002);
    minUnitCheck(testDevice.frameBuffer[5] == 0x0005);
    // test clearing
    testDevice.putPixel(18,1,0);
    minUnitCheck(testDevice.frameBuffer[5] == 0x0001);
}

MINUNIT_ADD(testSharpMemLcdFlipVcom, testSharpMemLcdSetup, testSharpMemLcdTeardown)
{
    minUnitCheck(testDevice.frameBuffer[0] == 0x0101);
    testDevice.flipVcom(stubTransfer);
    minUnitCheck(transfers.transferCount == 1);
    minUnitCheck(transfers.transferLength == 1);
    minUnitCheck(transfers.transfer[0] == 0x0103);
    minUnitCheck(testDevice.frameBuffer[0] == 0x0103);
    testDevice.flipVcom(stubTransfer);
    minUnitCheck(transfers.transferCount == 2);
    minUnitCheck(transfers.transferLength == 1);
    minUnitCheck(transfers.transfer[0] == 0x0101);
    minUnitCheck(testDevice.frameBuffer[0] == 0x0101);
}

MINUNIT_ADD(testStubTransfer, stubTransferReset, testSharpMemLcdTeardown)
{
    util::array<uint16_t, 4> testArray;
    minUnitCheck(transfers.transferCount == 0);
    minUnitCheck(transfers.transferLength == 0);
    stubTransfer(testArray.begin(), testArray.end());
    minUnitCheck(transfers.transferCount == 1);
    minUnitCheck(transfers.transferLength == 4);
}

MINUNIT_ADD(testClearBuffer, testSharpMemLcdSetup, testSharpMemLcdTeardown)
{
    minUnitCheck(testDevice.frameBuffer[1] == 0x0000);
    testDevice.setBuffer(0x55AA);
    minUnitCheck(testDevice.frameBuffer[2] == 0x55AA);
}

MINUNIT_ADD(testBitBlockTransfer, testSharpMemLcdSetup, testSharpMemLcdTeardown)
{
    uint8_t testSetBlock[4] = {0xFF, 0xFF, 0xFF, 0xFF};
    uint8_t testClearBlock[4] = {0x00, 0x00, 0x00, 0x00};
    // write single aligned line
    testDevice.setBuffer(0x0000);
    testDevice.bitBlockTransfer(0, 0, testSetBlock, 8, 1);
    minUnitCheck(testDevice.frameBuffer[0] == 0x0101);
    minUnitCheck(testDevice.frameBuffer[1] == 0x00FF);
    minUnitCheck(testDevice.frameBuffer[2] == 0x0000);
    minUnitCheck(testDevice.frameBuffer[3] == 0x0201);
    minUnitCheck(testDevice.frameBuffer[4] == 0x0000);
    minUnitCheck(testDevice.frameBuffer[5] == 0x0000);
    minUnitCheck(testDevice.frameBuffer[6] == 0x0301);
    // line cross check
    testDevice.setBuffer(0xFFFF);
    testDevice.bitBlockTransfer(1, 1, testClearBlock, 8, 2);
    minUnitCheck(testDevice.frameBuffer[0] == 0x0101);
    minUnitCheck(testDevice.frameBuffer[1] == 0xFFFF);
    minUnitCheck(testDevice.frameBuffer[2] == 0xFFFF);
    minUnitCheck(testDevice.frameBuffer[3] == 0x0201);
    minUnitCheck(testDevice.frameBuffer[4] == 0xFE01);
    minUnitCheck(testDevice.frameBuffer[5] == 0xFFFF);
    minUnitCheck(testDevice.frameBuffer[6] == 0x0301);
    minUnitCheck(testDevice.frameBuffer[7] == 0xFE01);
    minUnitCheck(testDevice.frameBuffer[8] == 0xFFFF);
    minUnitCheck(testDevice.frameBuffer[9] == 0x0401);
    minUnitCheck(testDevice.frameBuffer[10] == 0xFFFF);
    minUnitCheck(testDevice.frameBuffer[11] == 0xFFFF);
    // boundary cross check
    testDevice.setBuffer(0x0000);
    testDevice.bitBlockTransfer(14, 1, testSetBlock, 4, 2);
    minUnitCheck(testDevice.frameBuffer[0] == 0x0101);
    minUnitCheck(testDevice.frameBuffer[1] == 0x0000);
    minUnitCheck(testDevice.frameBuffer[2] == 0x0000);
    minUnitCheck(testDevice.frameBuffer[3] == 0x0201);
    minUnitCheck(testDevice.frameBuffer[4] == 0xC000);
    minUnitCheck(testDevice.frameBuffer[5] == 0x0003);
    minUnitCheck(testDevice.frameBuffer[6] == 0x0301);
    minUnitCheck(testDevice.frameBuffer[7] == 0xC000);
    minUnitCheck(testDevice.frameBuffer[8] == 0x0003);
    minUnitCheck(testDevice.frameBuffer[9] == 0x0401);
    minUnitCheck(testDevice.frameBuffer[10] == 0x0000);
    minUnitCheck(testDevice.frameBuffer[11] == 0x0000);
    minUnitCheck(testDevice.frameBuffer[12] == 0x0501);
    // bounds check X
    testDevice.setBuffer(0x0000);
    testDevice.bitBlockTransfer(30, 1, testSetBlock, 4, 2);
    minUnitCheck(testDevice.frameBuffer[0] == 0x0101);
    minUnitCheck(testDevice.frameBuffer[1] == 0x0000);
    minUnitCheck(testDevice.frameBuffer[2] == 0x0000);
    minUnitCheck(testDevice.frameBuffer[3] == 0x0201);
    minUnitCheck(testDevice.frameBuffer[4] == 0x0000);
    minUnitCheck(testDevice.frameBuffer[5] == 0xC000);
    minUnitCheck(testDevice.frameBuffer[6] == 0x0301);
    minUnitCheck(testDevice.frameBuffer[7] == 0x0000);
    minUnitCheck(testDevice.frameBuffer[8] == 0xC000);
    minUnitCheck(testDevice.frameBuffer[9] == 0x0401);
    minUnitCheck(testDevice.frameBuffer[10] == 0x0000);
    minUnitCheck(testDevice.frameBuffer[11] == 0x0000);
    minUnitCheck(testDevice.frameBuffer[12] == 0x0501);
    // check inversion
    testDevice.setBuffer(0x0000);
    testDevice.bitBlockTransfer(14, 1, testClearBlock, 4, 2, true);
    minUnitCheck(testDevice.frameBuffer[0] == 0x0101);
    minUnitCheck(testDevice.frameBuffer[1] == 0x0000);
    minUnitCheck(testDevice.frameBuffer[2] == 0x0000);
    minUnitCheck(testDevice.frameBuffer[3] == 0x0201);
    minUnitCheck(testDevice.frameBuffer[4] == 0xC000);
    minUnitCheck(testDevice.frameBuffer[5] == 0x0003);
    minUnitCheck(testDevice.frameBuffer[6] == 0x0301);
    minUnitCheck(testDevice.frameBuffer[7] == 0xC000);
    minUnitCheck(testDevice.frameBuffer[8] == 0x0003);
    minUnitCheck(testDevice.frameBuffer[9] == 0x0401);
    minUnitCheck(testDevice.frameBuffer[10] == 0x0000);
    minUnitCheck(testDevice.frameBuffer[11] == 0x0000);
    minUnitCheck(testDevice.frameBuffer[12] == 0x0501);


}

// TODO: update LCD with only modified lines