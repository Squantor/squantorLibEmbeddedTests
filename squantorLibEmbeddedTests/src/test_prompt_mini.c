/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
#include <MinUnit.h>
#include <prompt_mini.h>
#include <mock_datastreamchar.h>
#include <string.h>

char testPromptMiniBuffer[10];

result testPromptMiniHandler(char *const command);

promptData_t testPromptMiniData = 
{
    testPromptMiniBuffer,
    0,
    sizeof(testPromptMiniBuffer),
    testPromptMiniHandler,
};

char testPromptMiniHandlerbuf[10];

result testPromptMiniHandler(char *const command)
{
    strcpy(testPromptMiniHandlerbuf, command); 
    // return non standard value to check if everything is corrently passed
    return resultEnd;
}

int testPromptMiniLoop(int timeout)
{
    int counts = timeout;
    result r;
    do {
        r = promptProcess(&testPromptMiniData, &testDsChar);
        counts--;
    } while(r == noError && (counts > 0));
    return counts;
}

static void testPromptMiniSetup(minunitState *testResults) 
{
     mockDsCharReset();
     testPromptMiniData.bufferIndex = 0;
}

static void testPromptMiniTeardown(minunitState *testResults) 
{
}

MINUNIT_ADD(testPromptMiniEmpty, testPromptMiniSetup, testPromptMiniTeardown) 
{
    minUnitCheck(mockDsPutReadsString("\r") == noError);
    minUnitCheck(promptProcess(&testPromptMiniData, &testDsChar) == promptError);
}

MINUNIT_ADD(testPromptMiniNormal, testPromptMiniSetup, testPromptMiniTeardown) 
{
    minUnitCheck(mockDsPutReadsString("abcde\r") == noError);
    minUnitCheck(testPromptMiniLoop(5) == 0);
    minUnitCheck(promptProcess(&testPromptMiniData, &testDsChar) == resultEnd);
    minUnitCheck(strcmp(testPromptMiniHandlerbuf, "abcde") == 0);
}