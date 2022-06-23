/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * \file test_bitblit2d.cpp
 *
 * Bit blit 2d tests
 */

#include <MinUnit.h>
#include <string.h>
#include <stdint.h>
#include <bitblit.hpp>

MINUNIT_ADD(testBitBlit2DCases, NULL, NULL) {
  uint8_t src[] = {0x00, 0x00, 0x00, 0x00};
  uint8_t dest[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  // fully enclosed over boundary transfer
  memset(dest, 0xc5, sizeof(dest));
  memset(src, 0xFF, sizeof(src));
  util::bitblit2d(dest, 8, 8, 2, 2, src, 4, 4, util::bitblitOperation::OP_MOV);
  minUnitCheck(dest[0] == 0xc5);
  minUnitCheck(dest[1] == 0xc5);
  minUnitCheck(dest[2] == 0xFD);
  minUnitCheck(dest[3] == 0xFD);
  minUnitCheck(dest[4] == 0xFD);
  minUnitCheck(dest[5] == 0xFD);
  minUnitCheck(dest[6] == 0xc5);
  minUnitCheck(dest[7] == 0xc5);
  // fully enclosed aligned and remainder transfer
  memset(dest, 0x5c, sizeof(dest));
  memset(src, 0x29, sizeof(src));
  util::bitblit2d(dest, 16, 4, 0, 1, src, 12, 2, util::bitblitOperation::OP_MOV);
  minUnitCheck(dest[0] == 0x5c);
  minUnitCheck(dest[1] == 0x5c);
  minUnitCheck(dest[2] == 0x29);
  minUnitCheck(dest[3] == 0x59);
  minUnitCheck(dest[4] == 0x29);
  minUnitCheck(dest[5] == 0x59);
  minUnitCheck(dest[6] == 0x5c);
  minUnitCheck(dest[7] == 0x5c);
  // unaligned out of bounds transfer
  memset(dest, 0xAA, sizeof(dest));
  memset(src, 0x54, sizeof(src));
  util::bitblit2d(dest, 16, 4, 12, 1, src, 12, 2, util::bitblitOperation::OP_MOV);
  minUnitCheck(dest[0] == 0xAA);
  minUnitCheck(dest[1] == 0xAA);
  minUnitCheck(dest[2] == 0xAA);
  minUnitCheck(dest[3] == 0x4A);
  minUnitCheck(dest[4] == 0xAA);
  minUnitCheck(dest[5] == 0x4A);
  minUnitCheck(dest[6] == 0xAA);
  minUnitCheck(dest[7] == 0xAA);
  // aligned out of bounds transfer
  memset(dest, 0xCC, sizeof(dest));
  memset(src, 0xAA, sizeof(src));
  util::bitblit2d(dest, 16, 4, 8, 1, src, 12, 2, util::bitblitOperation::OP_MOV);
  minUnitCheck(dest[0] == 0xCC);
  minUnitCheck(dest[1] == 0xCC);
  minUnitCheck(dest[2] == 0xCC);
  minUnitCheck(dest[3] == 0xAA);
  minUnitCheck(dest[4] == 0xCC);
  minUnitCheck(dest[5] == 0xAA);
  minUnitCheck(dest[6] == 0xCC);
  minUnitCheck(dest[7] == 0xCC);
}