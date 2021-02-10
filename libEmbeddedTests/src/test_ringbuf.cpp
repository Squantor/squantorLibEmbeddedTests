/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/** 
 * \file test_ringbuf.cpp
 * 
 * All tests for the ring buffer class
 */ 
#include <MinUnit.h>
#include <stdint.h>
#include <ringbuf.hpp>

util::RingBuffer<uint16_t, 5> RingBufferDutU16;

MINUNIT_ADD(RingBufferCppEmpty)
{
    RingBufferDutU16.reset();
    minUnitCheck(RingBufferDutU16.empty() == true);
    minUnitCheck(RingBufferDutU16.full() == false);
}
