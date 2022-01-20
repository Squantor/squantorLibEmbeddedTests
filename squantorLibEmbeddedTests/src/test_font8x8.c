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
    minUnitCheck(ascii2font8x8Index[i] < sizeof(font8x8Horizontal));
  }
  const uint8_t* begin = &font8x8Horizontal[0];
  const uint8_t* end = &font8x8Horizontal[sizeof(font8x8Horizontal)];
  for (int i = 0; i < 128; i++) {
    const uint8_t* bitmapPtr = ascii2Font8x8(font8x8Horizontal, i);
    minUnitCheck(bitmapPtr >= begin);
    minUnitCheck(bitmapPtr < end);
  }
  begin = &font8x8Vertical[0];
  end = &font8x8Vertical[sizeof(font8x8Vertical)];
  for (int i = 0; i < 128; i++) {
    const uint8_t* bitmapPtr = ascii2Font8x8(font8x8Vertical, i);
    minUnitCheck(bitmapPtr >= begin);
    minUnitCheck(bitmapPtr < end);
  }
  begin = &font8x8VerticalFlipped[0];
  end = &font8x8VerticalFlipped[sizeof(font8x8VerticalFlipped)];
  for (int i = 0; i < 128; i++) {
    const uint8_t* bitmapPtr = ascii2Font8x8(font8x8VerticalFlipped, i);
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