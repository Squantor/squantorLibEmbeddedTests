/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
#include <string.h>
#include <MinUnit.h>
#include <cmdline_prompt.h>
#include <mock_datastreamchar.h>

char testCmdPromptStringBuffer[32];
t_queueString testCmdPromptStringQueue = {
    .mask = sizeof(testCmdPromptStringBuffer)-1,
    .head = 0,
    .tail = 0,
    .data = testCmdPromptStringBuffer,
    };

char testCmdlineParseString[128];
int testCmdlineParseCallCnt = 0;

result testCmdlineParse(char *cmdline)
{
    strncpy(testCmdlineParseString, cmdline, sizeof(testCmdlineParseString));
    testCmdlineParseCallCnt++;
    return noError;
}

int testCmdPromptLoop(int timeout)
{
    int counts = timeout;
    result r;
    do {
        r = cmdlinePromptProcess(&testDsChar, testCmdlineParse);
        counts--;
    } while(r == noError && (counts > 0));
    return counts;
}

static void testCmdPromptSetup(minunitState *testResults) 
{
    mockDsCharReset();
    testCmdPromptStringQueue.head = 0;
    testCmdPromptStringQueue.tail = 0;
    testCmdlineParseCallCnt = 0;
    memset(testCmdPromptStringBuffer, 0, sizeof(testCmdPromptStringBuffer));
    memset(testCmdlineParseString, 0, sizeof(testCmdlineParseString));
    cmdlinePromptInit(&testCmdPromptStringQueue);
    minUnitPass(); // supress warning
}

MINUNIT_ADD(testCmdPromptEmpty, testCmdPromptSetup, NULL) 
{
    minUnitCheck(testCmdPromptLoop(10) == 9);
}

// check if prompt echo works
MINUNIT_ADD(testCmdPromptCmdlineEcho, testCmdPromptSetup, NULL) 
{
    char testcmd[] = "foo";
    char testoutput[3] = "baz";
    mockDsPutReadsString(testcmd);
    minUnitCheck(testCmdPromptLoop(10) == 6);
    minUnitCheck(mockDsGetWrites(testoutput, sizeof(testoutput)) == noError);
    minUnitCheck(memcmp(testcmd, testoutput, 3) == 0);
}
// check line editing
MINUNIT_ADD(testCmdPromptCmdLineEdit, testCmdPromptSetup, NULL)
{
    char testcmd[] = "fa\booo\b";
    char testcmdexpect[11] = "fa\b \booo\b \b";
    char testcmdout[11];
    mockDsPutReadsString(testcmd);
    minUnitCheck(testCmdPromptLoop(10) == 2);
    minUnitCheck(mockDsGetWrites(testcmdout, sizeof(testcmdout)) == noError);
    minUnitCheck(mockDsGetWriteStatus() == queueEmpty);
    minUnitCheck(memcmp(testcmdout, testcmdexpect, 11) == 0);
}

// check what happens when we just press enter
MINUNIT_ADD(testCmdPromptCmdlineInputEmpty, testCmdPromptSetup, NULL) 
{
    char testcmd[] = "\r";
    char testcmdoutput[] = "\r";
    char testcmdout[11];
    mockDsPutReadsString(testcmd);
    minUnitCheck(testCmdPromptLoop(1) == 0);
    minUnitCheck(mockDsGetWrites(testcmdout, 1) == noError);
    minUnitCheck(mockDsGetWriteStatus() == queueEmpty);
    minUnitCheck(memcmp(testcmdout, testcmdoutput, 1) == 0);
}

// check if the command interpreter gets called
MINUNIT_ADD(testCmdPromptCmdlineInput, testCmdPromptSetup, NULL) 
{
    char testcmd[] = "foo\r";
    char testcmdcall[] = "foo";
    char testcmdoutput[] = "foo\r";
    char testcmdout[11];
    mockDsPutReadsString(testcmd);
    minUnitCheck(testCmdPromptLoop(10) == 5);
    minUnitCheck(mockDsGetWrites(testcmdout, 4) == noError);
    minUnitCheck(mockDsGetWriteStatus() == queueEmpty);
    minUnitCheck(memcmp(testcmdout, testcmdoutput, 4) == 0); 
    minUnitCheck(testCmdlineParseCallCnt == 1);
    minUnitCheck(strncmp(testcmdcall, testCmdlineParseString, sizeof(testcmdcall)) == 0);
}

// input unhandled escape, should be empty
MINUNIT_ADD(testCmdPromptCmdlineBadEsc, testCmdPromptSetup, NULL)
{
    char testcmd[] = "\e_";
    mockDsPutReadsString(testcmd);
    minUnitCheck(testCmdPromptLoop(10) == 7);
    minUnitCheck(mockDsGetWriteStatus() == queueEmpty);
}

// check if the command interpreter gets edited line
MINUNIT_ADD(testCmdPromptCmdlineEditInput, testCmdPromptSetup, NULL) 
{
    char testcmd[] = "fa\booo\b\r";
    char testcmdcall[] = "foo";
    char testcmdoutput[] = "fa\b \booo\b \b\r";
    char testcmdout[15];
    mockDsPutReadsString(testcmd);
    minUnitCheck(testCmdPromptLoop(10) == 1);
    minUnitCheck(mockDsGetWrites(testcmdout, 12) == noError);
    minUnitCheck(mockDsGetWriteStatus() == queueEmpty);
    minUnitCheck(memcmp(testcmdout, testcmdoutput, 12) == 0); 
    minUnitCheck(testCmdlineParseCallCnt == 1);
    minUnitCheck(strncmp(testcmdcall, testCmdlineParseString, sizeof(testcmdcall)) == 0);
}

// check if we can get previous command
MINUNIT_ADD(testCmdPromptRetrieve, testCmdPromptSetup, NULL) 
{
    char testcmd[] = "foo\r\e[A";
    char testcmdcall[] = "foo";
    char testcmdoutput[] = "foo\rfoo";
    char testcmdout[11];
    mockDsPutReadsString(testcmd);
    minUnitCheck(testCmdPromptLoop(7) == 0);
    minUnitCheck(mockDsGetWrites(testcmdout, 7) == noError);
    minUnitCheck(mockDsGetWriteStatus() == queueEmpty);
    minUnitCheck(memcmp(testcmdout, testcmdoutput, 4) == 0); 
    minUnitCheck(testCmdlineParseCallCnt == 1);
    minUnitCheck(strncmp(testcmdcall, testCmdlineParseString, sizeof(testcmdcall)) == 0);
}

// check if we can go up and down through history
MINUNIT_ADD(testCmdPromptRetrieveForBack, testCmdPromptSetup, NULL) 
{
    char testcmd[] = "bazz\r";
    char testcmdBackspace[] = "\b \b\b \b\b \b\b \bbazz";
    char testUp[] = "\e[A";
    char testDown[] = "\e[B";
    char testcmdoutput[20];
    // fill history while crossing boundaries
    for(int i = 0; i < 8; i++)
    {
        mockDsPutReadsString(testcmd);
        minUnitCheck(testCmdPromptLoop(5) == 0);
        minUnitCheck(mockDsGetWrites(testcmdoutput, 5) == noError);
        minUnitCheck(mockDsGetWriteStatus() == queueEmpty);
        minUnitCheck(memcmp(testcmd, testcmdoutput, 4) == 0);
        minUnitCheck(testCmdlineParseCallCnt == i+1);
    }
    
    // last command on empty prompt is different
    mockDsPutReadsString(testUp);
    minUnitCheck(testCmdPromptLoop(3) == 0);
    minUnitCheck(mockDsGetWrites(testcmdoutput, 4) == noError);
    minUnitCheck(mockDsGetWriteStatus() == queueEmpty);
    minUnitCheck(memcmp(testcmd, testcmdoutput, 4) == 0);
    minUnitCheck(testCmdlineParseCallCnt == 8);    
    
    // go back in history with a full prompt, go until the end
    for(int i = 0; i < 4; i++)
    {
        mockDsPutReadsString(testUp);
        minUnitCheck(testCmdPromptLoop(3) == 0);
        minUnitCheck(mockDsGetWrites(testcmdoutput, 16) == noError);
        minUnitCheck(mockDsGetWriteStatus() == queueEmpty);
        minUnitCheck(memcmp(testcmdBackspace, testcmdoutput, 16) == 0);
        minUnitCheck(testCmdlineParseCallCnt == 8);
    }
    
    // empty response check
    mockDsPutReadsString(testUp);
    minUnitCheck(testCmdPromptLoop(3) == 0);
    minUnitCheck(mockDsGetWriteStatus() == queueEmpty);
    
    // go forward in history
    for(int i = 0; i < 5; i++)
    {
        mockDsPutReadsString(testDown);
        minUnitCheck(testCmdPromptLoop(3) == 0);
        minUnitCheck(mockDsGetWrites(testcmdoutput, 16) == noError);
        minUnitCheck(mockDsGetWriteStatus() == queueEmpty);
        minUnitCheck(memcmp(testcmdBackspace, testcmdoutput, 16) == 0);
        minUnitCheck(testCmdlineParseCallCnt == 8);   
    }
    
    // empty response check
    mockDsPutReadsString(testDown);
    minUnitCheck(testCmdPromptLoop(3) == 0);
    minUnitCheck(mockDsGetWriteStatus() == queueEmpty);
}
