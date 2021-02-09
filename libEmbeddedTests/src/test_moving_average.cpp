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

util::movingAverage<uint16_t, 5> movingAverageDUTu16;

MINUNIT_ADD(movingAverageCppReset)
{
    movingAverageDUTu16.reset();
    minUnitCheck(movingAverageDUTu16.get() == 0);
    movingAverageDUTu16.add(10);
    minUnitCheck(movingAverageDUTu16.get() != 0);
    movingAverageDUTu16.reset();
    minUnitCheck(movingAverageDUTu16.get() == 0);
}