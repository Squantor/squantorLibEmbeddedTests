/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2023 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
#include <MinUnit.h>
#include <sq_coro.h>

static int voidCoroutineState;
static int voidCoroutineWait;
static int coroutineState;
static int coroutineWait;

static void testCoroutineSetup(minunitState *testResults) {
  voidCoroutineState = 42;
  voidCoroutineWait = 0;
  coroutineState = 42;
  coroutineWait = 0;
  minUnitPass();  // supress warning
}

static void testCoroutineTeardown(minunitState *testResults) {
  minUnitPass();  // supress warning
}

void dutCoroutineVoid(void) {
  CR_BEGIN;
  voidCoroutineState = 0;
  CR_YIELD_V;
  voidCoroutineState = 1;
  CR_YIELD_V;
  voidCoroutineState = 2;
  CR_YIELD_V;
  voidCoroutineState = 3;
  CR_WAIT_V(voidCoroutineWait == 1);
  voidCoroutineState = 4;
  CR_STOP_V;
  voidCoroutineState = 6;  // should never be executed
  CR_END_V;
}

int dutCoroutine(void) {
  CR_BEGIN;
  voidCoroutineState = 0;
  CR_YIELD(voidCoroutineState);
  voidCoroutineState = 1;
  CR_YIELD(voidCoroutineState);
  voidCoroutineState = 2;
  CR_YIELD(voidCoroutineState);
  voidCoroutineState = 3;
  CR_WAIT(voidCoroutineState, coroutineWait == 1);
  voidCoroutineState = 4;
  CR_STOP(voidCoroutineState);
  voidCoroutineState = 6;  // should never be executed
  CR_END(voidCoroutineState);
}

MINUNIT_ADD(testCoroutineVoid, testCoroutineSetup, testCoroutineTeardown) {
  minUnitCheck(voidCoroutineState == 42);
  dutCoroutineVoid();
  minUnitCheck(voidCoroutineState == 0);
  dutCoroutineVoid();
  minUnitCheck(voidCoroutineState == 1);
  dutCoroutineVoid();
  minUnitCheck(voidCoroutineState == 2);
  dutCoroutineVoid();
  minUnitCheck(voidCoroutineState == 3);
  dutCoroutineVoid();
  minUnitCheck(voidCoroutineState == 3);
  voidCoroutineWait = 1;
  dutCoroutineVoid();
  minUnitCheck(voidCoroutineState == 4);
  dutCoroutineVoid();
  minUnitCheck(voidCoroutineState == 0);
}

MINUNIT_ADD(testCoroutine, testCoroutineSetup, testCoroutineTeardown) {
  minUnitCheck(voidCoroutineState == 42);
  minUnitCheck(dutCoroutine() == 0);
  minUnitCheck(voidCoroutineState == 0);
  minUnitCheck(dutCoroutine() == 1);
  minUnitCheck(voidCoroutineState == 1);
  minUnitCheck(dutCoroutine() == 2);
  minUnitCheck(voidCoroutineState == 2);
  minUnitCheck(dutCoroutine() == 3);
  minUnitCheck(voidCoroutineState == 3);
  minUnitCheck(dutCoroutine() == 3);
  minUnitCheck(voidCoroutineState == 3);
  coroutineWait = 1;
  minUnitCheck(dutCoroutine() == 4);
  minUnitCheck(voidCoroutineState == 4);
  minUnitCheck(dutCoroutine() == 0);
  minUnitCheck(voidCoroutineState == 0);
}
