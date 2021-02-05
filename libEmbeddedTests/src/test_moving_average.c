/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/** 
 * \file test_moving_average.c
 * 
 * All tests for the moving average filter template macro
 */ 

#include <MinUnit.h>
#include <stdint.h>
#include <moving_average.h>

#define TESTU16_TYPE    uint16_t
#define TESTU16_SIZE    4

MOVING_AVERAGE_VARS(testU16, TESTU16_TYPE, TESTU16_SIZE);
MOVING_AVERAGE_PROTO(testU16, TESTU16_TYPE);
MOVING_AVERAGE_FUNCTIONS(testU16, TESTU16_TYPE, TESTU16_SIZE);

void movingAverageTestSetup(void)
{
    testU16Reset();
}

void movingAverageTestTeardown(void)
{

}

MINUNIT_ADD(movingAverageUint16Reset)
{
    minUnitCheck(testU16Get() == 0);
    testU16Add(10);
    minUnitCheck(testU16Get() != 0);
    testU16Reset();
    minUnitCheck(testU16Get() == 0);
}

MINUNIT_ADD(movingAverageUint16Get)
{
    minUnitCheck(testU16Get() == 0);
    testU16Add(1);
    testU16Add(2);
    testU16Add(3);
    testU16Add(4);
    minUnitCheck(testU16Get() == 2);
    testU16Add(5);
    minUnitCheck(testU16Get() == 3);
    testU16Add(6);
    minUnitCheck(testU16Get() == 4);
}