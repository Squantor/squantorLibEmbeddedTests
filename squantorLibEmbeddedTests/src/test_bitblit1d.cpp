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

MINUNIT_ADD(testBitBlit1D, NULL, NULL) {
  uint8_t testDest[3]{0x00, 0x00, 0x00};
  uint8_t testSrc[1]{0xFF};
  util::bitblit1d(testDest, sizeof(testDest), 0, testSrc, 8);
  minUnitCheck(testDest[0] == 0xFF);
}