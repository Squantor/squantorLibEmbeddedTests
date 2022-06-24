/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * \file test_elementpack.cpp
 *
 * elementpack test routines
 */

#include <MinUnit.h>
#include <string.h>
#include <stdint.h>
#include <bit/operations.hpp>
#include <bit/elementpack.hpp>

MINUNIT_ADD(testElementPackto8, NULL, NULL) {
  uint8_t src8[] = {0x5A, 0x5A, 0x5A, 0x5A, 0x5A};
  uint8_t dest8[] = {0x00};
  uint16_t dest16[] = {0x0000};
  uint32_t dest32[] = {0x00000000};
  // pack equal sized and aligned
  dest8[0] = 0xBB;
  util::elementPack(dest8, src8, 0, util::bitblitOperation::OP_MOV);
  minUnitCheck(dest8[0] == 0x5A);
  // pack equal sized and unaligned positive
  dest8[0] = 0xBB;
  util::elementPack(dest8, src8, 4, util::bitblitOperation::OP_MOV);
  minUnitCheck(dest8[0] == 0xA5);
  // pack equal sized and unaligned negative
  dest8[0] = 0xBB;
  util::elementPack(dest8, src8, -4, util::bitblitOperation::OP_MOV);
  minUnitCheck(dest8[0] == 0xB5);
  // pack unequal sized 16bit and aligned
  dest16[0] = 0xABCD;
  util::elementPack(dest16, src8, 0, util::bitblitOperation::OP_MOV);
  minUnitCheck(dest16[0] == 0x5A5A);
  // pack unequal sized 16bit and unaligned positive
  dest16[0] = 0xABCD;
  util::elementPack(dest16, src8, 4, util::bitblitOperation::OP_MOV);
  minUnitCheck(dest16[0] == 0xA5A5);
  // pack unequal sized 16bit and unaligned negative
  dest16[0] = 0xABCD;
  util::elementPack(dest16, src8, -4, util::bitblitOperation::OP_MOV);
  minUnitCheck(dest16[0] == 0xA5A5);
  // pack unequal sized 32bit and aligned
  dest32[0] = 0x12345678;
  util::elementPack(dest32, src8, 0, util::bitblitOperation::OP_MOV);
  minUnitCheck(dest32[0] == 0x5A5A5A5A);
  // pack unequal sized 32bit and unaligned positive
  dest32[0] = 0x12345678;
  util::elementPack(dest32, src8, 4, util::bitblitOperation::OP_MOV);
  minUnitCheck(dest32[0] == 0xA5A5A5A5);
  // pack unequal sized 32bit and unaligned negative
  dest32[0] = 0x12345678;
  util::elementPack(dest32, src8, -4, util::bitblitOperation::OP_MOV);
  minUnitCheck(dest32[0] == 0x15A5A5A5);
}