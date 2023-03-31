/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * \file test_parity.c
 *
 * All tests for parity functions
 */
#include <MinUnit.h>
#include <parity.h>

MINUNIT_ADD(testParityC, NULL, NULL) {
  // test cases from wikipedia
  minUnitCheck(false == sq_parityEven((uint8_t)0b0000000u));
  minUnitCheck(true == sq_parityEven((uint8_t)0b1010001u));
  minUnitCheck(false == sq_parityEven((uint8_t)0b1101001u));
  minUnitCheck(true == sq_parityEven((uint8_t)0b1111111u));

  minUnitCheck(true == sq_parityOdd((uint8_t)0b0000000u));
  minUnitCheck(false == sq_parityOdd((uint8_t)0b1010001u));
  minUnitCheck(true == sq_parityOdd((uint8_t)0b1101001u));
  minUnitCheck(false == sq_parityOdd((uint8_t)0b1111111u));

  // my own test cases
  minUnitCheck(false == sq_parityEven((uint8_t)0x03u));
  minUnitCheck(false == sq_parityEven((uint16_t)0x1001u));
  minUnitCheck(false == sq_parityEven((uint32_t)0x00303003u));
  minUnitCheck(false == sq_parityEven((uint64_t)0x0060060030033060u));
  minUnitCheck(true == sq_parityOdd((uint8_t)0x03u));
  minUnitCheck(true == sq_parityOdd((uint16_t)0x1001u));
  minUnitCheck(true == sq_parityOdd((uint32_t)0x00303003u));
  minUnitCheck(true == sq_parityOdd((uint64_t)0x0060060030033060u));
  minUnitCheck(true == sq_parityEven((uint8_t)0x10u));
  minUnitCheck(true == sq_parityEven((uint16_t)0x1110u));
  minUnitCheck(true == sq_parityEven((uint32_t)0x22220002u));
  minUnitCheck(true == sq_parityEven((uint64_t)0x8221000200020001u));
  minUnitCheck(false == sq_parityOdd((uint8_t)0x10u));
  minUnitCheck(false == sq_parityOdd((uint16_t)0x1110u));
  minUnitCheck(false == sq_parityOdd((uint32_t)0x22220002u));
  minUnitCheck(false == sq_parityOdd((uint64_t)0x8221000200020001u));
}
