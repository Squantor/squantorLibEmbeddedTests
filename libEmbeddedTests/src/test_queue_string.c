/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
#include <MinUnit.h>
#include <string.h>
#include <results.h>
#include <queue_string.h>

char testQueueStringBuffer[128];
t_queueString testQueue = {.mask = sizeof(testQueueStringBuffer)-1, .head = 0, .tail = 0, .data = testQueueStringBuffer};

void testSetupQueueString(void) 
{
    // clear queue
    testQueue.head = 0;
    testQueue.tail = 0;
    memset(testQueueStringBuffer, 0, sizeof(testQueueStringBuffer));
}

void testTeardownQueueString(void) 
{

}

MINUNIT_ADD(testEnqueue) 
{
    testSetupQueueString();
    minUnitCheck(queueStringEnqueue(NULL, NULL) == invalidArg);
    minUnitCheck(queueStringEnqueue(&testQueue, NULL) == invalidArg);
    
    char *stringEmpty = "";
    char stringMassive[128+20];
    char *stringNormal = "Hello World\n";
    char stringDummy[16] = "Dummy";
    memset(stringMassive, 'a', sizeof(stringMassive)-1);
    // zero terminate massive string
    stringMassive[sizeof(stringMassive)-1] = 0;
    // add empty string
    minUnitCheck(queueStringEnqueue(&testQueue, stringEmpty) == dataInvalid);
    // add too big string
    minUnitCheck(queueStringEnqueue(&testQueue, stringMassive) == dataInvalid);
    // add string
    minUnitCheck(queueStringEnqueue(&testQueue, stringNormal) == noError);
    // add so many strings you overflow the buffer a few times
    for(int i = 0; i < 200; i++)
    {
        minUnitCheck(queueStringEnqueue(&testQueue, stringDummy) == noError);
    }
    testTeardownQueueString();
}

MINUNIT_ADD(testDequeue) 
{
    testSetupQueueString();
    minUnitCheck(queueStringDequeue(NULL, NULL) == invalidArg);
    minUnitCheck(queueStringDequeue(&testQueue, NULL) == invalidArg);
    testTeardownQueueString();
}


MINUNIT_ADD(testEnqueueDequeue) 
{
    testSetupQueueString();
    char stringInput[] = "Hello World\n";
    char stringOutput[32];
    minUnitCheck(queueStringEnqueue(&testQueue, stringInput) == noError);
    minUnitCheck(queueStringDequeue(&testQueue, stringOutput) == noError);
    minUnitCheck(strcmp(stringInput, stringOutput) == 0);
    testTeardownQueueString();
}

MINUNIT_ADD(testEnqueueDequeueOverwrite) 
{
    testSetupQueueString();
    char stringDummy[16] = "Dummy";
    char stringOutput[32];
    // add so many strings you overflow the buffer a few times
    for(int i = 0; i < 50; i++)
    {
        minUnitCheck(queueStringEnqueue(&testQueue, stringDummy) == noError);
    }
    
    for(int i = 0; i < 20; i++)
    {
        minUnitCheck(queueStringDequeue(&testQueue, stringOutput) == noError);
        minUnitCheck(strcmp(stringDummy, stringOutput) == 0); 
    }
    minUnitCheck(queueStringDequeue(&testQueue, stringOutput) == queueEmpty);
    testTeardownQueueString();
}

MINUNIT_ADD(testGetPrev) 
{
    testSetupQueueString();
    uint16_t idx;
    char stringDummy[16] = "Dummy";
    char stringOutput[32];
    // add a bunch of strings that also overwrite old ones
    for(int i = 0; i < 34; i++)
    {
        queueStringEnqueue(&testQueue, stringDummy);
    }
    
    idx = testQueue.head;   
    for(int i = 33; i >= 14; i--)
    {
        minUnitCheck(queueStringPrev(&testQueue, &idx, stringOutput) == noError);
        minUnitCheck(strcmp(stringDummy, stringOutput) == 0);
    }
    minUnitCheck(queueStringPrev(&testQueue, &idx, stringOutput) == queueEmpty);
    testTeardownQueueString();
}

MINUNIT_ADD(testGetNext) 
{
    testSetupQueueString();
    uint16_t idx;
    char stringTest[] = "Test\n";
    char stringOutput[32];
    // First half fill
    for(int i = 0; i < 10; i++)
    {
        minUnitCheck(queueStringEnqueue(&testQueue, stringTest) == noError);
    }
    
    // move down
    idx = testQueue.head;
    for(int i = 0; i < 10; i++)
    {
        minUnitCheck(queueStringPrev(&testQueue, &idx, stringOutput) == noError);
    }
    minUnitCheck(queueStringPrev(&testQueue, &idx, stringOutput) == queueEmpty);
    // move up
    for(int i = 0; i < 10; i++)
    {
        minUnitCheck(queueStringNext(&testQueue, &idx, stringOutput) == noError);
        minUnitCheck(strcmp(stringTest, stringOutput) == 0);
    }
    minUnitCheck(queueStringNext(&testQueue, &idx, stringOutput) == queueEmpty);
    testTeardownQueueString();
}