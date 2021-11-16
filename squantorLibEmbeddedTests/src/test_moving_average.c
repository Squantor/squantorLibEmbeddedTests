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

#define TESTU32_TYPE    uint32_t
#define TESTU32_SIZE    3

MOVING_AVERAGE_VARS(testU32, TESTU32_TYPE, TESTU32_SIZE);
MOVING_AVERAGE_PROTO(testU32, TESTU32_TYPE);
MOVING_AVERAGE_FUNCTIONS(testU32, TESTU32_TYPE, TESTU32_SIZE);

#define TESTDOUBLE_TYPE    double
#define TESTDOUBLE_SIZE    5

MOVING_AVERAGE_VARS(testDouble, TESTDOUBLE_TYPE, TESTDOUBLE_SIZE);
MOVING_AVERAGE_PROTO(testDouble, TESTDOUBLE_TYPE);
MOVING_AVERAGE_FUNCTIONS(testDouble, TESTDOUBLE_TYPE, TESTDOUBLE_SIZE);

void movingAverageTestSetup(minunitState *testResults)
{
    testU16Reset();
    testU32Reset();
    testDoubleReset();
    minUnitPass(); // supress warning
}

MINUNIT_ADD(movingAverageUint16Reset, movingAverageTestSetup, NULL)
{
    minUnitCheck(testU16Get() == 0);
    testU16Add(10);
    minUnitCheck(testU16Get() != 0);
    testU16Reset();
    minUnitCheck(testU16Get() == 0);
}

MINUNIT_ADD(movingAverageUint16Get, movingAverageTestSetup, NULL)
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

MINUNIT_ADD(movingAverageUint32Get, movingAverageTestSetup, NULL)
{
    minUnitCheck(testU32Get() == 0);
    testU32Add(1);
    testU32Add(2);
    testU32Add(3);
    testU32Add(4);
    minUnitCheck(testU32Get() == 3);
    testU32Add(5);
    minUnitCheck(testU32Get() == 4);
    testU32Add(6);
    minUnitCheck(testU32Get() == 5);
}

MINUNIT_ADD(movingAverageDoubleGet, movingAverageTestSetup, NULL)
{
    minUnitCheck(testDoubleGet() == 0);
    testDoubleAdd(1.1);
    testDoubleAdd(2.2);
    testDoubleAdd(3.3);
    testDoubleAdd(4.4);
    minUnitCheck(testDoubleGet() == 2.2);
    testDoubleAdd(5);
    minUnitCheck(testDoubleGet() == 3.2);
    testDoubleAdd(6);
    minUnitCheck(testDoubleGet() == 4.18);
}