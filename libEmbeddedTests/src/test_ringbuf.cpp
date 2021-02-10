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

MINUNIT_ADD(RingBufferCppPushBack)
{
    uint16_t number = 42;
    RingBufferDutU16.reset();
    minUnitCheck(RingBufferDutU16.empty() == true);
    minUnitCheck(RingBufferDutU16.PushBack(number) == true);
    minUnitCheck(RingBufferDutU16.empty() == false);
}

MINUNIT_ADD(RingBufferCppPushBackFull)
{
    uint16_t number = 42;
    RingBufferDutU16.reset();
    minUnitCheck(RingBufferDutU16.empty() == true);
    for(uint16_t i = 0; i < 10; i++)
    {
        minUnitCheck(RingBufferDutU16.PushBack(i) == true);
    }
    minUnitCheck(RingBufferDutU16.PushBack(number) == false);
    minUnitCheck(RingBufferDutU16.full() == true);
}

MINUNIT_ADD(RingBufferCppPushFront)
{
    uint16_t number = 42;
    RingBufferDutU16.reset();
    minUnitCheck(RingBufferDutU16.empty() == true);
    minUnitCheck(RingBufferDutU16.PushFront(number) == true);
    minUnitCheck(RingBufferDutU16.empty() == false);
}

MINUNIT_ADD(RingBufferCppPushFrontFull)
{
    uint16_t number = 42;
    RingBufferDutU16.reset();
    minUnitCheck(RingBufferDutU16.empty() == true);
    for(uint16_t i = 0; i < 10; i++)
    {
        minUnitCheck(RingBufferDutU16.PushFront(i) == true);
    }
    minUnitCheck(RingBufferDutU16.PushFront(number) == false);
    minUnitCheck(RingBufferDutU16.full() == true);
}

MINUNIT_ADD(RingBufferCppPopBack)
{
    uint16_t number = 42;
    uint16_t output = 0;
    RingBufferDutU16.reset();
    minUnitCheck(RingBufferDutU16.PopBack(output) == false);
    minUnitCheck(RingBufferDutU16.PushFront(number) == true);
    minUnitCheck(RingBufferDutU16.PopBack(output) == true);
    minUnitCheck(output == 42);
    minUnitCheck(RingBufferDutU16.PopBack(output) == false);
    for(uint16_t i = 0; i < 10; i++)
    {
        RingBufferDutU16.PushFront(i);
    }
    for(uint16_t i = 0; i < 10; i++)
    {
        minUnitCheck(RingBufferDutU16.PopBack(output) == true);
        minUnitCheck(output == i);
    }
    minUnitCheck(RingBufferDutU16.PopBack(output) == false);
    for(uint16_t i = 0; i < 10; i++)
    {
        RingBufferDutU16.PushBack(i);
    }
    for(uint16_t i = 0; i < 10; i++)
    {
        minUnitCheck(RingBufferDutU16.PopBack(output) == true);
        minUnitCheck(output == 9 - i);
    }
    minUnitCheck(RingBufferDutU16.PopBack(output) == false);
}

MINUNIT_ADD(RingBufferCppPopFront)
{
    uint16_t number = 42;
    uint16_t output = 0;
    minUnitCheck(RingBufferDutU16.PopFront(output) == false);
    minUnitCheck(RingBufferDutU16.PushFront(number) == true);
    minUnitCheck(RingBufferDutU16.PopFront(output) == true);
    minUnitCheck(output == 42);
    minUnitCheck(RingBufferDutU16.PopFront(output) == false);
    for(uint16_t i = 0; i < 10; i++)
    {
        RingBufferDutU16.PushFront(i);
    }
    for(int i = 9; i >= 0; i--)
    {
        minUnitCheck(RingBufferDutU16.PopFront(output) == true);
        minUnitCheck(output == i);
    }
    minUnitCheck(RingBufferDutU16.PopFront(output) == false);
    for(uint16_t i = 0; i < 10; i++)
    {
        RingBufferDutU16.PushBack(i);
    }
    for(uint16_t i = 0; i < 10; i++)
    {
        minUnitCheck(RingBufferDutU16.PopFront(output) == true);
        minUnitCheck(output == i);
    }
    minUnitCheck(RingBufferDutU16.PopFront(output) == false);
}