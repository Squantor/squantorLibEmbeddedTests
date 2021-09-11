/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
#include <MinUnit.h>
#include <sharp_memlcd.hpp>


using lcdTestConfig = util::lcdConfig<32,32>;
util::sharpMemLcd<lcdTestConfig> testDevice;

static void testSharpMemLcdSetup(minunitState *testResults) 
{
    testDevice.init();
    testResults = testResults; /*!< supress warning */
}

static void testSharpMemLcdTeardown(minunitState *testResults) 
{
    testResults = testResults; /*!< supress warning */
}

MINUNIT_ADD(testSharpMemLcdInit, testSharpMemLcdSetup, testSharpMemLcdTeardown) 
{
    minUnitCheck(testDevice.frameBuffer[0] == 0x8001);
    minUnitCheck(testDevice.frameBuffer[3] == 0x0000);
    minUnitCheck(testDevice.frameBuffer[8] == 0x8003);
    minUnitCheck(testDevice.frameBuffer[124] == 0x8020);
}

MINUNIT_ADD(testSharpMemLcdPutPixel, testSharpMemLcdSetup, testSharpMemLcdTeardown) 
{
    testDevice.putPixel(0,0,1);
    testDevice.putPixel(1,1,1);
    testDevice.putPixel(18,1,1);
    testDevice.putPixel(16,1,1);
    minUnitCheck(testDevice.frameBuffer[1] == 0x0001);
    minUnitCheck(testDevice.frameBuffer[5] == 0x0002);
    minUnitCheck(testDevice.frameBuffer[6] == 0x0005);
    // test clearing
    testDevice.putPixel(18,1,0);
    minUnitCheck(testDevice.frameBuffer[6] == 0x0001);
}
