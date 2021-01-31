/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
#include <MinUnit.h>
#include <queue.h>

#define TESTQUEUECHARSIZE   6
char testQueueCharBuf[TESTQUEUECHARSIZE];
queueChar_t testQueueChar = {
    TESTQUEUECHARSIZE,
    0,
    0,
    testQueueCharBuf,
    };

static void testQueueSetup(void) 
{
    queueInit(&testQueueChar);
}

static void testQueueTeardown(void) 
{

}

MINUNIT_ADD(testQueueEmpty) 
{
    char c;
    testQueueSetup();
    minUnitCheck(queueDequeue(&testQueueChar, &c) == queueEmpty);
    testQueueTeardown();
}

MINUNIT_ADD(testQueueEnqDeq) 
{
    char in = 'a';
    char out = 'q';
    testQueueSetup();
    for(int i = 0; i < TESTQUEUECHARSIZE-1; i++)
    {
        minUnitCheck(queueEnqueue(&testQueueChar, in + i) == noError);
    }
    minUnitCheck(queueState(&testQueueChar) == queueFull);
    minUnitCheck(queueEnqueue(&testQueueChar, in) == queueFull);
    
    for(int i = 0; i < TESTQUEUECHARSIZE-1; i++)
    {
        minUnitCheck(queueDequeue(&testQueueChar, &out) == noError);
        minUnitCheck(out == in + i);
    }
    minUnitCheck(queueDequeue(&testQueueChar, &out) == queueEmpty);
    // check if out has been unmodified
    minUnitCheck(out == in + TESTQUEUECHARSIZE-2);
    
    // We do again a test, but now we will cross the max boundary
    minUnitCheck(queueState(&testQueueChar) == queueEmpty);
    minUnitCheck(queueEnqueue(&testQueueChar, in) == noError);
    minUnitCheck(queueState(&testQueueChar) == queueNotEmpty);
    minUnitCheck(queueDequeue(&testQueueChar, &out) == noError);   
    minUnitCheck(queueState(&testQueueChar) == queueEmpty); 
    minUnitCheck(queueDequeue(&testQueueChar, &out) == queueEmpty);
    minUnitCheck(out == in);
    testQueueTeardown();
}