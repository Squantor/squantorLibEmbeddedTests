/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * \file test_bitblit1d.cpp
 *
 * Bit blit 1d tests
 */

#include <MinUnit.h>
#include <string.h>
#include <stdint.h>
#include <bitblit.hpp>

MINUNIT_ADD(testBitBlit1DCases, NULL, NULL) {
  // we add one extra byte as canary to check out of bound writes
  uint8_t testDest[5]{0x00, 0x00, 0x00, 0x00, 0x00};
  uint8_t testSrc[3]{0xFF, 0xFF, 0xFF};
  size_t testDestSize = sizeof(testDest) - 1;  // subtract one for canary
  // single byte aligned
  memset(testDest, 0, sizeof(testDest));
  util::bitblit1d(testDest, testDestSize, 8, testSrc, 8);
  minUnitCheck(testDest[1] == 0xFF);
  // single byte crossing boundary
  memset(testDest, 0, sizeof(testDest));
  util::bitblit1d(testDest, testDestSize, 3, testSrc, 8);
  minUnitCheck(testDest[0] == 0xF8);
  minUnitCheck(testDest[1] == 0x07);
  // single byte crossing boundary at the edge
  memset(testDest, 0, sizeof(testDest));
  util::bitblit1d(testDest, testDestSize, 28, testSrc, 8);
  minUnitCheck(testDest[3] == 0xF0);
  minUnitCheck(testDest[4] == 0x00);
  // two byte aligned
  memset(testDest, 0, sizeof(testDest));
  util::bitblit1d(testDest, testDestSize, 8, testSrc, 16);
  minUnitCheck(testDest[1] == 0xFF);
  minUnitCheck(testDest[2] == 0xFF);
  // two byte crossing boundary
  // n byte aligned
  // n byte aligned but with dangling few bits (special case)
  // n byte crossing boundary
  // less then one byte aligned
  // less then one byte crossing
}

MINUNIT_ADD(testBitBlit1DOperations, NULL, NULL) {
  minUnitPass();
}