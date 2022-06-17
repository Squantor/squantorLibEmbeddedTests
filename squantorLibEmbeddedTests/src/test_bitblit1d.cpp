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
  uint8_t testSrc[4]{0xFF, 0xFF, 0xFF, 0xFF};
  size_t testDestSize = sizeof(testDest) - 1;  // subtract one for canary
  // less then one byte aligned
  memset(testDest, 0, sizeof(testDest));
  util::bitblit1d(testDest, testDestSize, 16, testSrc, 5);
  minUnitCheck(testDest[2] == 0x1F);
  // less then one byte crossing
  memset(testDest, 0, sizeof(testDest));
  util::bitblit1d(testDest, testDestSize, 8, testSrc, 3);
  minUnitCheck(testDest[1] == 0x07);
  // single byte aligned
  memset(testDest, 0, sizeof(testDest));
  util::bitblit1d(testDest, testDestSize, 8, testSrc, 8);
  minUnitCheck(testDest[1] == 0xFF);
  // single byte aligned crossing boundary
  memset(testDest, 0, sizeof(testDest));
  util::bitblit1d(testDest, testDestSize, 16, testSrc, 10);
  minUnitCheck(testDest[2] == 0xFF);
  minUnitCheck(testDest[3] == 0x03);
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
  // two byte aligned, crossing boundary
  memset(testDest, 0, sizeof(testDest));
  util::bitblit1d(testDest, testDestSize, 8, testSrc, 20);
  minUnitCheck(testDest[1] == 0xFF);
  minUnitCheck(testDest[2] == 0xFF);
  minUnitCheck(testDest[3] == 0x0F);
  // two byte crossing boundary
  memset(testDest, 0, sizeof(testDest));
  util::bitblit1d(testDest, testDestSize, 10, testSrc, 16);
  minUnitCheck(testDest[1] == 0xFC);
  minUnitCheck(testDest[2] == 0xFF);
  minUnitCheck(testDest[3] == 0x03);
  minUnitCheck(testDest[4] == 0x00);
  // n byte aligned
  memset(testDest, 0, sizeof(testDest));
  util::bitblit1d(testDest, testDestSize, 0, testSrc, 24);
  minUnitCheck(testDest[0] == 0xFF);
  minUnitCheck(testDest[1] == 0xFF);
  minUnitCheck(testDest[2] == 0xFF);
  minUnitCheck(testDest[4] == 0x00);
  // n byte aligned crossing boundary
  memset(testDest, 0, sizeof(testDest));
  util::bitblit1d(testDest, testDestSize, 0, testSrc, 28);
  minUnitCheck(testDest[0] == 0xFF);
  minUnitCheck(testDest[1] == 0xFF);
  minUnitCheck(testDest[2] == 0xFF);
  minUnitCheck(testDest[3] == 0x0F);
  minUnitCheck(testDest[4] == 0x00);
  // n byte crossing boundary
  memset(testDest, 0, sizeof(testDest));
  util::bitblit1d(testDest, testDestSize, 2, testSrc, 28);
  minUnitCheck(testDest[0] == 0xFC);
  minUnitCheck(testDest[1] == 0xFF);
  minUnitCheck(testDest[2] == 0xFF);
  minUnitCheck(testDest[3] == 0x03);
  minUnitCheck(testDest[4] == 0x00);
  // n byte crossing boundary at the edge
  memset(testDest, 0, sizeof(testDest));
  util::bitblit1d(testDest, testDestSize, 20, testSrc, 28);
  minUnitCheck(testDest[2] == 0xF0);
  minUnitCheck(testDest[3] == 0xFF);
  minUnitCheck(testDest[4] == 0x00);
}

MINUNIT_ADD(testBitBlit1DOperations, NULL, NULL) {
  minUnitPass();
}