/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * \file test_parity.cpp
 *
 * All tests for parity functions
 */
#include <MinUnit.h>
#include <parity.hpp>

using namespace util;

MINUNIT_ADD(testParityCpp, NULL, NULL) {
  // test cases from wikipedia
  minUnitCheck(false == parityEven(static_cast<uint8_t>(0b0000000u)));
  minUnitCheck(true == parityEven(static_cast<uint8_t>(0b1010001u)));
  minUnitCheck(false == parityEven(static_cast<uint8_t>(0b1101001u)));
  minUnitCheck(true == parityEven(static_cast<uint8_t>(0b1111111u)));

  minUnitCheck(true == parityOdd(0b0000000u));
  minUnitCheck(false == parityOdd(0b1010001u));
  minUnitCheck(true == parityOdd(0b1101001u));
  minUnitCheck(false == parityOdd(0b1111111u));

  // my own test cases
  minUnitCheck(false == parityEven(0x03u));
  minUnitCheck(false == parityEven(0x1001u));
  minUnitCheck(false == parityEven(0x00303003u));
  minUnitCheck(false == parityEven(0x0060060030033060u));
  minUnitCheck(true == parityOdd(0x03u));
  minUnitCheck(true == parityOdd(0x1001u));
  minUnitCheck(true == parityOdd(0x00303003u));
  minUnitCheck(true == parityOdd(0x0060060030033060u));
  minUnitCheck(true == parityEven(0x10u));
  minUnitCheck(true == parityEven(0x1110u));
  minUnitCheck(true == parityEven(0x22220002u));
  minUnitCheck(true == parityEven(0x8221000200020001u));
  minUnitCheck(false == parityOdd(0x10u));
  minUnitCheck(false == parityOdd(0x1110u));
  minUnitCheck(false == parityOdd(0x22220002u));
  minUnitCheck(false == parityOdd(0x8221000200020001u));
}