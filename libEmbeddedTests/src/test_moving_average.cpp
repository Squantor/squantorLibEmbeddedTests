/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/** 
 * \file test_moving_average.cpp
 * 
 * All tests for the moving average filter class
 */ 

#include <MinUnit.h>
#include <stdint.h>
#include <moving_average.hpp>

util::MovingAverage<uint16_t, 5> movingAverageDutU16(0);
util::MovingAverage<uint32_t, 3> movingAverageDutU32(0);
util::MovingAverage<double, 4> movingAverageDutDouble(0);

MINUNIT_ADD(movingAverageCppReset)
{
    movingAverageDutU16.reset(0);
    minUnitCheck(movingAverageDutU16.get() == 0);
    movingAverageDutU16.add(10);
    minUnitCheck(movingAverageDutU16.get() != 0);
    movingAverageDutU16.reset(0);
    minUnitCheck(movingAverageDutU16.get() == 0);
    movingAverageDutU16.reset(10);
    minUnitCheck(movingAverageDutU16.get() == 10);
    movingAverageDutU16.reset(0);
    minUnitCheck(movingAverageDutU16.get() == 0);
}

MINUNIT_ADD(MovingAverageCppAverage)
{
    movingAverageDutU16.reset(0);
    movingAverageDutU16.add(1);
    minUnitCheck(movingAverageDutU16.get() == 0);
    movingAverageDutU16.add(2);
    minUnitCheck(movingAverageDutU16.get() == 0);
    movingAverageDutU16.add(3);
    minUnitCheck(movingAverageDutU16.get() == 1);
    movingAverageDutU16.add(4);
    minUnitCheck(movingAverageDutU16.get() == 2);
    movingAverageDutU16.add(5);
    minUnitCheck(movingAverageDutU16.get() == 3);
    movingAverageDutU16.add(5);
    movingAverageDutU16.add(6);
    movingAverageDutU16.add(7);
    minUnitCheck(movingAverageDutU16.get() == 5);
}

MINUNIT_ADD(MovingAverageCppU32)
{
    movingAverageDutU32.reset(0);
    movingAverageDutU32.add(5);
    movingAverageDutU32.add(5);
    movingAverageDutU32.add(5);
    minUnitCheck(movingAverageDutU32.get() == 5);
    movingAverageDutU32.add(42);
    minUnitCheck(movingAverageDutU32.get() == 17);
}

MINUNIT_ADD(MovingAverageCppDouble)
{
    movingAverageDutDouble.reset(0);
    movingAverageDutDouble.add(1.5);
    minUnitCheck(movingAverageDutDouble.get() == 0.375);
    movingAverageDutDouble.add(2.5);
    minUnitCheck(movingAverageDutDouble.get() == 1.0);
    movingAverageDutDouble.add(3.5);
    minUnitCheck(movingAverageDutDouble.get() == 1.875);
    movingAverageDutDouble.add(4.5);
    minUnitCheck(movingAverageDutDouble.get() == 3);
}