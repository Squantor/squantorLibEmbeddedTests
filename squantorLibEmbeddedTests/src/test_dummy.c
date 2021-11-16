/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
#include <MinUnit.h>

static void testDummySetup(minunitState *testResults) 
{
    minUnitPass(); // supress warning
}

static void testDummyTeardown(minunitState *testResults) 
{
    minUnitPass(); // supress warning
}

MINUNIT_ADD(testDummyNormal, testDummySetup, testDummyTeardown) 
{
    minUnitCheck(1 == 1);
}
