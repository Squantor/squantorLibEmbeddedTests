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

}

void ringbufMacroTeardown(void)
{

}


MINUNIT_ADD(ringbufEmpty)
{
    ringbufMacroSetup();
    testReset();
    minUnitCheck(testEmpty() == true);
    minUnitCheck(testFull() == false);
    ringbufMacroTeardown();
}