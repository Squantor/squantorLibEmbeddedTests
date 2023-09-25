/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2023 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
#include <MinUnit.h>
#include <coroutine.hpp>

class coroutineVoid {
 public:
  coroutineVoid() : crCurrent{nullptr, false} {}
  ~coroutineVoid() = default;

  void coroutine(void) {
    CR_BEGIN;
    coroutineState = 0;
    CR_YIELD_V;
    coroutineState = 1;
    CR_YIELD_V;
    coroutineState = 2;
    CR_YIELD_V;
    coroutineState = 3;
    CR_WAIT_V(coroutineWait == 1);
    coroutineState = 4;
    CR_STOP_V;
    coroutineState = 6;  // should never be executed
    CR_END_V;
  }

  crState crCurrent;
  int coroutineState;
  int coroutineWait;
};

class coroutineNonVoid {
 public:
  coroutineNonVoid() = default;
  ~coroutineNonVoid() = default;

  int coroutine(void) {
    CR_BEGIN;
    coroutineState = 0;
    CR_YIELD(coroutineState);
    coroutineState = 1;
    CR_YIELD(coroutineState);
    coroutineState = 2;
    CR_YIELD(coroutineState);
    coroutineState = 3;
    CR_WAIT(coroutineState, coroutineWait == 1);
    coroutineState = 4;
    CR_STOP(coroutineState);
    coroutineState = 6;  // should never be executed
    CR_END(coroutineState);
  }

  crState crCurrent;
  int coroutineState;
  int coroutineWait;
};

coroutineVoid testCoroutineVoid;
coroutineNonVoid testCoroutineNonVoid;

static void testCoroutineSetup(minunitState *testResults) {
  testCoroutineVoid.crCurrent.initialized = false;
  testCoroutineVoid.coroutineState = 42;
  testCoroutineVoid.coroutineWait = 0;
  testCoroutineNonVoid.crCurrent.initialized = false;
  testCoroutineNonVoid.coroutineState = 42;
  testCoroutineNonVoid.coroutineWait = 0;
  minUnitPass();  // supress warning
}

static void testCoroutineTeardown(minunitState *testResults) {
  minUnitPass();  // supress warning
}

MINUNIT_ADD(testCoroutineVoid, testCoroutineSetup, testCoroutineTeardown) {
  minUnitCheck(testCoroutineVoid.coroutineState == 42);
  testCoroutineVoid.coroutine();
  minUnitCheck(testCoroutineVoid.coroutineState == 0);
  testCoroutineVoid.coroutine();
  minUnitCheck(testCoroutineVoid.coroutineState == 1);
  testCoroutineVoid.coroutine();
  minUnitCheck(testCoroutineVoid.coroutineState == 2);
  testCoroutineVoid.coroutine();
  minUnitCheck(testCoroutineVoid.coroutineState == 3);
  testCoroutineVoid.coroutine();
  minUnitCheck(testCoroutineVoid.coroutineState == 3);
  testCoroutineVoid.coroutineWait = 1;
  testCoroutineVoid.coroutine();
  minUnitCheck(testCoroutineVoid.coroutineState == 4);
  testCoroutineVoid.coroutine();
  minUnitCheck(testCoroutineVoid.coroutineState == 0);
}

MINUNIT_ADD(testCoroutine, testCoroutineSetup, testCoroutineTeardown) {
  minUnitCheck(testCoroutineNonVoid.coroutineState == 42);
  minUnitCheck(testCoroutineNonVoid.coroutine() == 0);
  minUnitCheck(testCoroutineNonVoid.coroutineState == 0);
  minUnitCheck(testCoroutineNonVoid.coroutine() == 1);
  minUnitCheck(testCoroutineNonVoid.coroutineState == 1);
  minUnitCheck(testCoroutineNonVoid.coroutine() == 2);
  minUnitCheck(testCoroutineNonVoid.coroutineState == 2);
  minUnitCheck(testCoroutineNonVoid.coroutine() == 3);
  minUnitCheck(testCoroutineNonVoid.coroutineState == 3);
  minUnitCheck(testCoroutineNonVoid.coroutine() == 3);
  minUnitCheck(testCoroutineNonVoid.coroutineState == 3);
  testCoroutineNonVoid.coroutineWait = 1;
  minUnitCheck(testCoroutineNonVoid.coroutine() == 4);
  minUnitCheck(testCoroutineNonVoid.coroutineState == 4);
  minUnitCheck(testCoroutineNonVoid.coroutine() == 0);
  minUnitCheck(testCoroutineNonVoid.coroutineState == 0);
}
