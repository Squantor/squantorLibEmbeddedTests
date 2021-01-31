/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
#include <MinUnit.h>
#include <command_mini.h>
#include <string.h>

const char testcmd1[] = "abc";
const char testcmd2[] = "def";

int handleCmd1Count;
int handleCmd2Count;
char handleCmd1Arg[16];
char handleCmd2Arg[16];

result testHandleCmd1(const char *argument)
{
    handleCmd1Count++;
    if(argument != NULL)
        strncpy(handleCmd1Arg, argument, sizeof(handleCmd1Arg));
    return noError;
}

result testHandleCmd2(const char *argument)
{
    handleCmd2Count++;
    if(argument != NULL)
        strncpy(handleCmd2Arg, argument, sizeof(handleCmd2Arg));
    return resultEnd;
}

commandEntry_t testlist[] = {
    {testcmd1, testHandleCmd1},
    {testcmd2, testHandleCmd2},
    {NULL, NULL},
    };

static void testCommandMiniSetup(void) 
{
    handleCmd1Count = 0;
    handleCmd2Count = 0;
    memset(handleCmd1Arg, 0, sizeof(handleCmd1Arg));
    memset(handleCmd2Arg, 0, sizeof(handleCmd2Arg));
}

static void testCommandMiniTeardown(void) 
{
    
}

MINUNIT_ADD(testCommandMiniNormal)
{
    testCommandMiniSetup();
    minUnitCheck(commandInterpret(testlist, "abc") == noError);
    minUnitCheck(handleCmd1Count == 1);
    minUnitCheck(commandInterpret(testlist, "def") == resultEnd);
    minUnitCheck(handleCmd2Count == 1);
    testCommandMiniTeardown();
}

MINUNIT_ADD(testCommandMiniNormalArg)
{
    testCommandMiniSetup();
    minUnitCheck(commandInterpret(testlist, "abc 123") == noError);
    minUnitCheck(handleCmd1Count == 1); 
    minUnitCheck(strncmp(handleCmd1Arg, "123", sizeof(handleCmd1Arg)) == 0);
    minUnitCheck(commandInterpret(testlist, "def 0x1234") == resultEnd);
    minUnitCheck(handleCmd2Count == 1); 
    minUnitCheck(strncmp(handleCmd2Arg, "0x1234", sizeof(handleCmd2Arg)) == 0);
    testCommandMiniTeardown();
}

MINUNIT_ADD(testCommandMiniFail) 
{
    testCommandMiniSetup();
    minUnitCheck(commandInterpret(testlist, "ghi") == commandNotFound);
    minUnitCheck(handleCmd1Count == 0);
    minUnitCheck(handleCmd2Count == 0);
    testCommandMiniTeardown();
}
