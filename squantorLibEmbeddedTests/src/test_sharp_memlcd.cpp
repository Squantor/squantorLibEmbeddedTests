/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
#include <MinUnit.h>
#include <sharp_memlcd.hpp>


using lcdTestConfig = util::lcdConfig<32,32, 8>;
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
    testDevice.flipVcom();
    minUnitCheck(testDevice.frameBuffer[0] == 0x0103);
    testDevice.flipVcom();
    minUnitCheck(testDevice.frameBuffer[0] == 0x0101);
}
