/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
#include <MinUnit.h>

static void testDummySetup(void) 
{
    
}

static void testDummyTeardown(void) 
{

}

MINUNIT_ADD(testDummyNormal) 
{
    testDummySetup();
    minUnitCheck(1 == 1);
    testDummyTeardown();
}
