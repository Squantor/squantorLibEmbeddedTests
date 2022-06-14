/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
#include <MinUnit.h>
#include <fonts/font_8x8.hpp>

MINUNIT_ADD(testMono8x8Col, NULL, NULL) {
  const uint8_t* begin = mono8x8Col.fontBitmap;
  const uint8_t* end = mono8x8Col.fontBitmap + mono8x8Col.fontBitmapSize;
  for (int i = 0; i < 128; i++) {
    minUnitCheck(mono8x8Col.ascii2index[i] < 760);
    const uint8_t* bitmapPtr = ascii2Font(mono8x8Col, i);
    minUnitCheck(bitmapPtr >= begin);
    minUnitCheck(bitmapPtr < end);
  }
}

MINUNIT_ADD(testMono8x8Row, NULL, NULL) {
  const uint8_t* begin = mono8x8Row.fontBitmap;
  const uint8_t* end = mono8x8Row.fontBitmap + mono8x8Row.fontBitmapSize;
  for (int i = 0; i < 128; i++) {
    minUnitCheck(mono8x8Row.ascii2index[i] < 760);
    const uint8_t* bitmapPtr = ascii2Font(mono8x8Row, i);
    minUnitCheck(bitmapPtr >= begin);
    minUnitCheck(bitmapPtr < end);
  }
}

MINUNIT_ADD(testMono8x8RowFlip, NULL, NULL) {
  const uint8_t* begin = mono8x8RowFlip.fontBitmap;
  const uint8_t* end = mono8x8RowFlip.fontBitmap + mono8x8RowFlip.fontBitmapSize;
  for (int i = 0; i < 128; i++) {
    minUnitCheck(mono8x8RowFlip.ascii2index[i] < 760);
    const uint8_t* bitmapPtr = ascii2Font(mono8x8RowFlip, i);
    minUnitCheck(bitmapPtr >= begin);
    minUnitCheck(bitmapPtr < end);
  }
}

/*

Useful generator to create flipped versions

#include <stdio.h>

MINUNIT_ADD(generator, NULL, NULL) {
  for (int i = 32; i < 128; i++) {
    const uint8_t* bitmapPtr = ascii2Font8x8(font8x8Horizontal, i);
    for (int j = 0; j < 8; j++) {
      uint8_t mask = 0x01 << j;
      uint8_t output = 0;

      output |= *(bitmapPtr + 0) & mask ? 0x01 : 0x00;
      output |= *(bitmapPtr + 1) & mask ? 0x02 : 0x00;
      output |= *(bitmapPtr + 2) & mask ? 0x04 : 0x00;
      output |= *(bitmapPtr + 3) & mask ? 0x08 : 0x00;
      output |= *(bitmapPtr + 4) & mask ? 0x10 : 0x00;
      output |= *(bitmapPtr + 5) & mask ? 0x20 : 0x00;
      output |= *(bitmapPtr + 6) & mask ? 0x40 : 0x00;
      output |= *(bitmapPtr + 7) & mask ? 0x80 : 0x00;
      printf("0x%02X, ", output);
    }
    printf("// U+00%02X (%c)\n", i, i);
  }
  minUnitPass();
}
*/