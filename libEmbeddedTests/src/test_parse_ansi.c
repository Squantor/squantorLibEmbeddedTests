/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
#include <MinUnit.h>
#include <parse_ansi.h>

void testParseAnsiSetup(void) 
{
}

void testParseAnsiTeardown(void) 
{
}

MINUNIT_ADD(testParseAnsiEmpty) 
{
    testParseAnsiSetup();
    minUnitCheck(ansiParse('a') == ansiError);
    testParseAnsiTeardown();
}

MINUNIT_ADD(testParseAnsiUnknownEscapes)
{
    testParseAnsiSetup();
    minUnitCheck(ansiParse('\e') == ansiEntered);
    minUnitCheck(ansiParse('_') == ansiError);
    minUnitCheck(ansiParse('\e') == ansiEntered);
    minUnitCheck(ansiParse('[') == ansiBrackOpen);
    minUnitCheck(ansiParse('_') == ansiError);    
    testParseAnsiTeardown();
}

MINUNIT_ADD(testParseAnsiCursorUp)
{
    testParseAnsiSetup();
    minUnitCheck(ansiParse('\e') == ansiEntered);
    minUnitCheck(ansiParse('[') == ansiBrackOpen);
    minUnitCheck(ansiParse('A') == ansiCursorUp);
    testParseAnsiTeardown();
}

MINUNIT_ADD(testParseAnsiCursorForward)
{
    testParseAnsiSetup();
    minUnitCheck(ansiParse('\e') == ansiEntered);
    minUnitCheck(ansiParse('[') == ansiBrackOpen);
    minUnitCheck(ansiParse('C') == ansiCursorForward);
    testParseAnsiTeardown();
}

MINUNIT_ADD(testParseAnsiInvalidValidInvalid)
{
    testParseAnsiSetup();
    minUnitCheck(ansiParse('a') == ansiError);
    minUnitCheck(ansiParse('\e') == ansiEntered);
    minUnitCheck(ansiParse('[') == ansiBrackOpen);
    minUnitCheck(ansiParse('C') == ansiCursorForward);
    minUnitCheck(ansiParse('a') == ansiError);
    testParseAnsiTeardown();
}