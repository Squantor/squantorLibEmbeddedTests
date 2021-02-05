/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/** 
 * \file test_ringbuf_macro.c
 * 
 * Main program entry point
 * 
 * Program execution starts here in main().
 */ 
#include <MinUnit.h>
#include <ringbuf_macro.h>

TEMPLATE_RINGBUF_VARS(test, int, 10);
TEMPLATE_RINGBUF_PROTO(test, int);
TEMPLATE_RINGBUF_FUNCTIONS(test, int, 10);

void ringbufMacroSetup(void)
{
    testReset();
}

void ringbufMacroTeardown(void)
{

}

MINUNIT_ADD(ringbufEmpty)
{
    ringbufMacroSetup();
    minUnitCheck(testEmpty() == true);
    minUnitCheck(testFull() == false);
    ringbufMacroTeardown();
}

MINUNIT_ADD(ringbufPushBack)
{
    int number = 42;
    ringbufMacroSetup();
    minUnitCheck(testEmpty() == true);
    minUnitCheck(testPushBack(&number) == true);
    minUnitCheck(testEmpty() == false);
    ringbufMacroTeardown();
}

MINUNIT_ADD(ringbufPushBackFull)
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

MINUNIT_ADD(ringbufPushFront)
{
    int number = 42;
    ringbufMacroSetup();
    minUnitCheck(testEmpty() == true);
    minUnitCheck(testPushFront(&number) == true);
    minUnitCheck(testEmpty() == false);
    ringbufMacroTeardown();
}

MINUNIT_ADD(ringbufPushFrontFull)
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

MINUNIT_ADD(ringbufPopBack)
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
    ringbufMacroTeardown();
}