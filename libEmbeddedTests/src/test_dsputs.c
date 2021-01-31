/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
#include <string.h>
#include <MinUnit.h>
#include <datastream.h>
#include <mock_datastreamchar.h>

static void testdsPutsSetup(void) 
{
    mockDsCharReset();
}

static void testdsPutsTeardown(void) 
{

}

MINUNIT_ADD(testdsPutsNormal) 
{
    testdsPutsSetup();
    char testInput[] = "abc";
    char testOutput[] = "abc";
    char testBuffer[12];
    minUnitCheck(dsPuts(&testDsChar, testInput) == noError);
    minUnitCheck(mockDsGetWrites(testBuffer, 3) == noError);
    minUnitCheck(mockDsGetWriteStatus() == queueEmpty);
    minUnitCheck(memcmp(testOutput, testBuffer, 3) == 0);
    testdsPutsTeardown();
}
