/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
#include <MinUnit.h>
#include <datastream.h>
#include <mock_datastreamchar.h>

static void testDsWriteSetup(minunitState *testResults) 
{
    mockDsCharReset();
}

static void testDsWriteTeardown(minunitState *testResults) 
{

}

MINUNIT_ADD(testDsWriteCharNormal, testDsWriteSetup, testDsWriteTeardown) 
{
    minUnitCheck(dsWriteElement(&testDsChar, 'a') == noError);
    minUnitCheck(dsWriteElement(&testDsChar, 'b') == noError);
    // TODO check amount of elements added maybe?
}