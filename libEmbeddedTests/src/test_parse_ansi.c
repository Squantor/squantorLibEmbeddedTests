/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
#include <MinUnit.h>
#include <parse_ansi.h>

void testParseAnsiSetup(minunitState *testResults) 
{
}

void testParseAnsiTeardown(minunitState *testResults) 
{
}

MINUNIT_ADD(testParseAnsiEmpty, testParseAnsiSetup, testParseAnsiTeardown) 
{
    minUnitCheck(ansiParse('a') == ansiError);
}

MINUNIT_ADD(testParseAnsiUnknownEscapes, testParseAnsiSetup, testParseAnsiTeardown)
{
    minUnitCheck(ansiParse('\e') == ansiEntered);
    minUnitCheck(ansiParse('_') == ansiError);
    minUnitCheck(ansiParse('\e') == ansiEntered);
    minUnitCheck(ansiParse('[') == ansiBrackOpen);
    minUnitCheck(ansiParse('_') == ansiError);    
}

MINUNIT_ADD(testParseAnsiCursorUp, testParseAnsiSetup, testParseAnsiTeardown)
{
    minUnitCheck(ansiParse('\e') == ansiEntered);
    minUnitCheck(ansiParse('[') == ansiBrackOpen);
    minUnitCheck(ansiParse('A') == ansiCursorUp);
}

MINUNIT_ADD(testParseAnsiCursorForward, testParseAnsiSetup, testParseAnsiTeardown)
{
    minUnitCheck(ansiParse('\e') == ansiEntered);
    minUnitCheck(ansiParse('[') == ansiBrackOpen);
    minUnitCheck(ansiParse('C') == ansiCursorForward);
}

MINUNIT_ADD(testParseAnsiInvalidValidInvalid, testParseAnsiSetup, testParseAnsiTeardown)
{
    minUnitCheck(ansiParse('a') == ansiError);
    minUnitCheck(ansiParse('\e') == ansiEntered);
    minUnitCheck(ansiParse('[') == ansiBrackOpen);
    minUnitCheck(ansiParse('C') == ansiCursorForward);
    minUnitCheck(ansiParse('a') == ansiError);
}