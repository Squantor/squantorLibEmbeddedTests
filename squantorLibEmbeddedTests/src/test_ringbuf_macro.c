/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/** 
 * \file test_ringbuf_macro.c
 * 
 * All tests for the ring buffer template macro
 */ 
#include <MinUnit.h>
#include <ringbuf_macro.h>

RINGBUF_VARS(test, int, 10);
RINGBUF_PROTO(test, int);
RINGBUF_FUNCTIONS(test, int, 10);

void ringbufMacroSetup(void)
{
    testReset();
}

void ringbufMacroTeardown(void)
{

}

MINUNIT_ADD(ringbufEmpty, NULL, NULL)
{
    ringbufMacroSetup();
    minUnitCheck(testEmpty() == true);
    minUnitCheck(testFull() == false);
    ringbufMacroTeardown();
}

MINUNIT_ADD(ringbufPushBack, NULL, NULL)
{
    int number = 42;
    ringbufMacroSetup();
    minUnitCheck(testEmpty() == true);
    minUnitCheck(testPushBack(&number) == true);
    minUnitCheck(testEmpty() == false);
    ringbufMacroTeardown();
}

MINUNIT_ADD(ringbufPushBackFull, NULL, NULL)
{
    int number = 42;
    ringbufMacroSetup();
    minUnitCheck(testEmpty() == true);
    for(int i = 0; i < 10; i++)
    {
        minUnitCheck(testPushBack(&i) == true);
    }
    minUnitCheck(testPushBack(&number) == false);
    minUnitCheck(testFull() == true);
    ringbufMacroTeardown();
}

MINUNIT_ADD(ringbufPushFront, NULL, NULL)
{
    int number = 42;
    ringbufMacroSetup();
    minUnitCheck(testEmpty() == true);
    minUnitCheck(testPushFront(&number) == true);
    minUnitCheck(testEmpty() == false);
    ringbufMacroTeardown();
}

MINUNIT_ADD(ringbufPushFrontFull, NULL, NULL)
{
    int number = 42;
    ringbufMacroSetup();
    minUnitCheck(testEmpty() == true);
    for(int i = 0; i < 10; i++)
    {
        minUnitCheck(testPushFront(&i) == true);
    }
    minUnitCheck(testPushFront(&number) == false);
    minUnitCheck(testFull() == true);
    ringbufMacroTeardown();
}

MINUNIT_ADD(ringbufPopBack, NULL, NULL)
{
    int number = 42;
    int output = 0;
    ringbufMacroSetup();
    minUnitCheck(testPopBack(&output) == false);
    minUnitCheck(testPushFront(&number) == true);
    minUnitCheck(testPopBack(&output) == true);
    minUnitCheck(output == 42);
    minUnitCheck(testPopBack(&output) == false);
    for(int i = 0; i < 10; i++)
    {
        testPushFront(&i);
    }
    for(int i = 0; i < 10; i++)
    {
        minUnitCheck(testPopBack(&output) == true);
        minUnitCheck(output == i);
    }
    minUnitCheck(testPopBack(&output) == false);
    for(int i = 0; i < 10; i++)
    {
        testPushBack(&i);
    }
    for(int i = 9; i >= 0; i--)
    {
        minUnitCheck(testPopBack(&output) == true);
        minUnitCheck(output == i);
    }
    minUnitCheck(testPopBack(&output) == false);
    ringbufMacroTeardown();
}

MINUNIT_ADD(ringbufPopFront, NULL, NULL)
{
    int number = 42;
    int output = 0;
    ringbufMacroSetup();
    minUnitCheck(testPopFront(&output) == false);
    minUnitCheck(testPushFront(&number) == true);
    minUnitCheck(testPopFront(&output) == true);
    minUnitCheck(output == 42);
    minUnitCheck(testPopFront(&output) == false);
    for(int i = 0; i < 10; i++)
    {
        testPushFront(&i);
    }
    for(int i = 9; i >= 0; i--)
    {
        minUnitCheck(testPopFront(&output) == true);
        minUnitCheck(output == i);
    }
    minUnitCheck(testPopFront(&output) == false);
    for(int i = 0; i < 10; i++)
    {
        testPushBack(&i);
    }
    for(int i = 0; i < 10; i++)
    {
        minUnitCheck(testPopFront(&output) == true);
        minUnitCheck(output == i);
    }
    minUnitCheck(testPopFront(&output) == false);
    ringbufMacroTeardown();
}