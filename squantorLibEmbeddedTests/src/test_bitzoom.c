/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2022 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
#include <MinUnit.h>
#include <bit.h>

MINUNIT_ADD(testBitZoom, NULL, NULL) {
  minUnitCheck(bitZoom(0x00) == 0x0000);
  minUnitCheck(bitZoom(0x01) == 0x0003);
  minUnitCheck(bitZoom(0x10) == 0x0300);
  minUnitCheck(bitZoom(0xA5) == 0xCC33);
}
