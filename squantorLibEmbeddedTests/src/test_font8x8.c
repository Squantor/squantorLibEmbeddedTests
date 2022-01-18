/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
#include <MinUnit.h>
#include <font_8x8.h>

MINUNIT_ADD(testFont8x8, NULL, NULL) {
  for (int i = 0; i < 128; i++) {
    minUnitCheck(ascii2font8x8[i] < sizeof(font8x8));
  }
}