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

MINUNIT_ADD(testElementPack8to8, NULL, NULL) {
  uint8_t src[] = {0x00, 0x00};
  uint8_t dest[] = {0x00};
  minUnitPass();
}