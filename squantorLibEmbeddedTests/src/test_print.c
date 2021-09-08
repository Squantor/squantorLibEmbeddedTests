/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
#include <string.h>
#include <MinUnit.h>
#include <print.h>
#include <mock_datastreamchar.h>

static void testPrintSetup(minunitState *testResults) 
{
    mockDsCharReset();
}

static void testPrintTeardown(minunitState *testResults) 
{

}

MINUNIT_ADD(testPrintDigit, testPrintSetup, testPrintTeardown) 
{
    char testZero[] = "0";
    char testNine[] = "9";
    char testA[] = "A";
    char testF[] = "F";
    char testOutput[4];
    minUnitCheck(printDigit(&testDsChar, 0) == noError);
    minUnitCheck(mockDsGetWrites(testOutput, 1) == noError);
    minUnitCheck(mockDsGetWriteStatus() == queueEmpty);
    minUnitCheck(memcmp(testOutput, testZero, 1) == 0);
    minUnitCheck(printDigit(&testDsChar, 9) == noError);
    minUnitCheck(mockDsGetWrites(testOutput, 1) == noError);
    minUnitCheck(mockDsGetWriteStatus() == queueEmpty);
    minUnitCheck(memcmp(testOutput, testNine, 1) == 0);
    minUnitCheck(printDigit(&testDsChar, 0x0A) == noError);
    minUnitCheck(mockDsGetWrites(testOutput, 1) == noError);
    minUnitCheck(mockDsGetWriteStatus() == queueEmpty);
    minUnitCheck(memcmp(testOutput, testA, 1) == 0);
    minUnitCheck(printDigit(&testDsChar, 0x0F) == noError);
    minUnitCheck(mockDsGetWrites(testOutput, 1) == noError);
    minUnitCheck(mockDsGetWriteStatus() == queueEmpty);
    minUnitCheck(memcmp(testOutput, testF, 1) == 0);
}

MINUNIT_ADD(testPrintHexU8, testPrintSetup, testPrintTeardown) 
{
    char testA6[] = "A6";
    char testOutput[4];
    minUnitCheck(printHex(&testDsChar, (uint8_t) 0xA6) == noError);
    minUnitCheck(mockDsGetWrites(testOutput, 2) == noError);
    minUnitCheck(mockDsGetWriteStatus() == queueEmpty);
    minUnitCheck(memcmp(testOutput, testA6, 2) == 0);
}

MINUNIT_ADD(testPrintHexU16, testPrintSetup, testPrintTeardown) 
{
    char test1B2C[] = "1B2C";
    char testOutput[4];
    minUnitCheck(printHex(&testDsChar, (uint16_t) 0x1B2C) == noError);
    minUnitCheck(mockDsGetWrites(testOutput, 4) == noError);
    minUnitCheck(mockDsGetWriteStatus() == queueEmpty);
    minUnitCheck(memcmp(testOutput, test1B2C, 4) == 0);
}

MINUNIT_ADD(testPrintHexU32, testPrintSetup, testPrintTeardown) 
{
    char test3D4E5F67[] = "3D4E5F67";
    char testOutput[8];
    minUnitCheck(printHex(&testDsChar, (uint32_t) 0x3D4E5F67) == noError);
    minUnitCheck(mockDsGetWrites(testOutput, 8) == noError);
    minUnitCheck(mockDsGetWriteStatus() == queueEmpty);
    minUnitCheck(memcmp(testOutput, test3D4E5F67, 8) == 0);
}

MINUNIT_ADD(testPrintDecU16, testPrintSetup, testPrintTeardown)
{
    char test00000[] = "00000";
    char test12345[] = "12345";
    char test65535[] = "65535";
    char testOutput[8];
    minUnitCheck(printDec(&testDsChar, (uint16_t) 0) == noError);
    minUnitCheck(mockDsGetWrites(testOutput, 5) == noError);
    minUnitCheck(mockDsGetWriteStatus() == queueEmpty);
    minUnitCheck(memcmp(testOutput, test00000, 5) == 0);
    minUnitCheck(printDec(&testDsChar, (uint16_t) 12345) == noError);
    minUnitCheck(mockDsGetWrites(testOutput, 5) == noError);
    minUnitCheck(mockDsGetWriteStatus() == queueEmpty);
    minUnitCheck(memcmp(testOutput, test12345, 5) == 0);
    minUnitCheck(printDec(&testDsChar, (uint16_t) 65535) == noError);
    minUnitCheck(mockDsGetWrites(testOutput, 5) == noError);
    minUnitCheck(mockDsGetWriteStatus() == queueEmpty);
    minUnitCheck(memcmp(testOutput, test65535, 5) == 0);
}

MINUNIT_ADD(testPrintDecNzU16, testPrintSetup, testPrintTeardown)
{
    char test0[] = "0";
    char test10[] = "10";
    char test100[] = "100";
    char test1000[] = "1000";
    char test10000[] = "10000";
    char test12345[] = "12345";
    char test65535[] = "65535";
    char testOutput[8];
    minUnitCheck(printDecNz(&testDsChar, (uint16_t) 0) == noError);
    minUnitCheck(mockDsGetWrites(testOutput, 1) == noError);
    minUnitCheck(mockDsGetWriteStatus() == queueEmpty);
    minUnitCheck(memcmp(testOutput, test0, 1) == 0);
    
    minUnitCheck(printDecNz(&testDsChar, (uint16_t) 10) == noError);
    minUnitCheck(mockDsGetWrites(testOutput, 2) == noError);
    minUnitCheck(mockDsGetWriteStatus() == queueEmpty);
    minUnitCheck(memcmp(testOutput, test10, 2) == 0);
    
    minUnitCheck(printDecNz(&testDsChar, (uint16_t) 100) == noError);
    minUnitCheck(mockDsGetWrites(testOutput, 3) == noError);
    minUnitCheck(mockDsGetWriteStatus() == queueEmpty);
    minUnitCheck(memcmp(testOutput, test100, 3) == 0);
    
    minUnitCheck(printDecNz(&testDsChar, (uint16_t) 1000) == noError);
    minUnitCheck(mockDsGetWrites(testOutput, 4) == noError);
    minUnitCheck(mockDsGetWriteStatus() == queueEmpty);
    minUnitCheck(memcmp(testOutput, test1000, 4) == 0);
    
    minUnitCheck(printDecNz(&testDsChar, (uint16_t) 10000) == noError);
    minUnitCheck(mockDsGetWrites(testOutput, 5) == noError);
    minUnitCheck(mockDsGetWriteStatus() == queueEmpty);
    minUnitCheck(memcmp(testOutput, test10000, 5) == 0);
    
    minUnitCheck(printDecNz(&testDsChar, (uint16_t) 12345) == noError);
    minUnitCheck(mockDsGetWrites(testOutput, 5) == noError);
    minUnitCheck(mockDsGetWriteStatus() == queueEmpty);
    minUnitCheck(memcmp(testOutput, test12345, 5) == 0);
    
    minUnitCheck(printDecNz(&testDsChar, (uint16_t) 65535) == noError);
    minUnitCheck(mockDsGetWrites(testOutput, 5) == noError);
    minUnitCheck(mockDsGetWriteStatus() == queueEmpty);
    minUnitCheck(memcmp(testOutput, test65535, 5) == 0);
}

MINUNIT_ADD(testPrintDecU32, testPrintSetup, testPrintTeardown)
{
    char test0000000000[] = "0000000000";
    char test1234567890[] = "1234567890";
    char test4294967295[] = "4294967295";
    char testOutput[10];
    minUnitCheck(printDec(&testDsChar, (uint32_t) 0) == noError);
    minUnitCheck(mockDsGetWrites(testOutput, 10) == noError);
    minUnitCheck(mockDsGetWriteStatus() == queueEmpty);
    minUnitCheck(memcmp(testOutput, test0000000000, 10) == 0);
    minUnitCheck(printDec(&testDsChar, (uint32_t) 1234567890) == noError);
    minUnitCheck(mockDsGetWrites(testOutput, 10) == noError);
    minUnitCheck(mockDsGetWriteStatus() == queueEmpty);
    minUnitCheck(memcmp(testOutput, test1234567890, 10) == 0);
    minUnitCheck(printDec(&testDsChar, (uint32_t) 4294967295) == noError);
    minUnitCheck(mockDsGetWrites(testOutput, 10) == noError);
    minUnitCheck(mockDsGetWriteStatus() == queueEmpty);
    minUnitCheck(memcmp(testOutput, test4294967295, 10) == 0);
}

MINUNIT_ADD(testPrintBinU32, testPrintSetup, testPrintTeardown)
{
    char test01011010111100001111111100000000[] = "01011010111100001111111100000000";
    char testOutput[32];
    minUnitCheck(printBin(&testDsChar, (uint32_t) 1525743360) == noError);
    minUnitCheck(mockDsGetWrites(testOutput, 32) == noError);
    minUnitCheck(mockDsGetWriteStatus() == queueEmpty);
    minUnitCheck(memcmp(testOutput, test01011010111100001111111100000000, 32) == 0);
}
