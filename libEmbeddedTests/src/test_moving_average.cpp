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

util::movingAverage<uint16_t, 5> movingAverageDutU16;
