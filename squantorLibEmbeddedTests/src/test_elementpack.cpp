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

// TODO, make source a bit more different to detect bugs
MINUNIT_ADD(testElementPackto8, NULL, NULL) {
  uint8_t src8[] = {0x5A, 0x29, 0x9C, 0xF3, 0x4D};
  uint8_t dest8[] = {0x00};
  uint16_t dest16[] = {0x0000};
  uint32_t dest32[] = {0x00000000};
  // pack equal sized 8bit and aligned
  dest8[0] = 0xBB;
  util::elementPack(dest8, src8, 0, util::bitblitOperation::OP_MOV);
  minUnitCheck(dest8[0] == 0x5A);
  // pack equal sized 8bit and unaligned positive
  dest8[0] = 0xBB;
  util::elementPack(dest8, src8, 4, util::bitblitOperation::OP_MOV);
  minUnitCheck(dest8[0] == 0xA2);
  // pack equal sized 8bit and unaligned negative
  dest8[0] = 0xBB;
  util::elementPack(dest8, src8, -4, util::bitblitOperation::OP_MOV);
  minUnitCheck(dest8[0] == 0xB5);
  // pack unequal sized 16bit and aligned
  dest16[0] = 0xABCD;
  util::elementPack(dest16, src8, 0, util::bitblitOperation::OP_MOV);
  minUnitCheck(dest16[0] == 0x5A29);
  // pack unequal sized 16bit and unaligned positive
  dest16[0] = 0xABCD;
  util::elementPack(dest16, src8, 4, util::bitblitOperation::OP_MOV);
  minUnitCheck(dest16[0] == 0xA299);
  // pack unequal sized 16bit and unaligned negative
  dest16[0] = 0xABCD;
  util::elementPack(dest16, src8, -4, util::bitblitOperation::OP_MOV);
  minUnitCheck(dest16[0] == 0xA5A2);
  // pack unequal sized 32bit and aligned
  dest32[0] = 0x12345678;
  util::elementPack(dest32, src8, 0, util::bitblitOperation::OP_MOV);
  minUnitCheck(dest32[0] == 0x5A299CF3);
  // pack unequal sized 32bit and unaligned positive
  dest32[0] = 0x12345678;
  util::elementPack(dest32, src8, 4, util::bitblitOperation::OP_MOV);
  minUnitCheck(dest32[0] == 0xA299CF34);
  // pack unequal sized 32bit and unaligned negative
  dest32[0] = 0x12345678;
  util::elementPack(dest32, src8, -4, util::bitblitOperation::OP_MOV);
  minUnitCheck(dest32[0] == 0x15A299CF);
}

MINUNIT_ADD(testElementPackto16, NULL, NULL) {
  uint16_t src16[] = {0x285A, 0xF24E, 0x339B};
  uint16_t dest16[] = {0x0000};
  uint32_t dest32[] = {0x00000000};
  // pack unequal sized 16bit and aligned
  dest16[0] = 0xABCD;
  util::elementPack(dest16, src16, 0, util::bitblitOperation::OP_MOV);
  minUnitCheck(dest16[0] == 0x285A);
  // pack unequal sized 16bit and unaligned positive
  dest16[0] = 0xABCD;
  util::elementPack(dest16, src16, 4, util::bitblitOperation::OP_MOV);
  minUnitCheck(dest16[0] == 0x85AF);
  // pack unequal sized 16bit and unaligned negative
  dest16[0] = 0xABCD;
  util::elementPack(dest16, src16, -4, util::bitblitOperation::OP_MOV);
  minUnitCheck(dest16[0] == 0xA285);
  // pack unequal sized 32bit and aligned
  dest32[0] = 0x12345678;
  util::elementPack(dest32, src16, 0, util::bitblitOperation::OP_MOV);
  minUnitCheck(dest32[0] == 0x285AF24E);
  // pack unequal sized 32bit and unaligned positive
  dest32[0] = 0x12345678;
  util::elementPack(dest32, src16, 4, util::bitblitOperation::OP_MOV);
  minUnitCheck(dest32[0] == 0x85AF24E3);
  // pack unequal sized 32bit and unaligned negative
  dest32[0] = 0x12345678;
  util::elementPack(dest32, src16, -4, util::bitblitOperation::OP_MOV);
  minUnitCheck(dest32[0] == 0x1285AF24);
}