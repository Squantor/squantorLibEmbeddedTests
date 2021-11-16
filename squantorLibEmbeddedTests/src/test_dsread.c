/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
#include <MinUnit.h>
#include <datastream.h>
#include <mock_datastreamchar.h>

char testabc[] = "abc";

static void testDsReadSetup(minunitState *testResults) 
{
    mockDsCharReset();
    minUnitPass(); // supress warning
}

MINUNIT_ADD(testDsReadCharNormal, testDsReadSetup, NULL) 
{
    char c;
    minUnitCheck(mockDsPutReads(testabc, sizeof(testabc)) == noError);
    minUnitCheck(dsReadElement(&testDsChar, &c) == noError);
    minUnitCheck(c == 'a');
    minUnitCheck(dsReadElement(&testDsChar, &c) == noError);
    minUnitCheck(c == 'b');
    minUnitCheck(dsReadElement(&testDsChar, &c) == noError);
    minUnitCheck(c == 'c');
    minUnitCheck(dsReadElement(&testDsChar, &c) == noError);
    minUnitCheck(c == '\0');
    minUnitCheck(dsReadElement(&testDsChar, &c) == streamEmtpy);
}
