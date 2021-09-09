/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
#include <MinUnit.h>
#include <sharp_memlcd.hpp>


util::sharpMemLcd<32,32> testDevice;

static void testSharpMemLcdSetup(minunitState *testResults) 
{
    testResults = testResults; /*!< supress warning */
}

static void testSharpMemLcdTeardown(minunitState *testResults) 
{
    testResults = testResults; /*!< supress warning */
}

MINUNIT_ADD(testSharpMemLcdInit, testSharpMemLcdSetup, testSharpMemLcdTeardown) 
{
    testDevice.init();
    minUnitCheck(testDevice.frameBuffer[0] == 0x8001);
    minUnitCheck(testDevice.frameBuffer[3] == 0x0000);
    minUnitCheck(testDevice.frameBuffer[8] == 0x8003);
    minUnitCheck(testDevice.frameBuffer[124] == 0x8020);
}
