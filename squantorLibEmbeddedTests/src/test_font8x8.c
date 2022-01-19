/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
#include <MinUnit.h>
#include <font_8x8.h>

MINUNIT_ADD(testFont8x8, NULL, NULL) {
  const uint8_t* begin = &font8x8[0];
  const uint8_t* end = &font8x8[sizeof(font8x8)];
  for (int i = 0; i < 128; i++) {
    minUnitCheck(ascii2font8x8Index[i] < sizeof(font8x8));
    const uint8_t* bitmapPtr = ascii2Font8x8(i);
    minUnitCheck(bitmapPtr >= begin);
    minUnitCheck(bitmapPtr < end);
  }
}