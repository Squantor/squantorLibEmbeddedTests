/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2023 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */

#include <format.hpp>
#include <MinUnit.h>
#include <cstring>
#include <array>

MINUNIT_ADD(testFormatAppendString, nullptr, nullptr) {
  std::array<char, 20> input;
  std::array<char, 20> output{"firstsecond"};
  std::array<char, 8> first{"first"};
  std::array<char, 8> second{"second"};

  minUnitCheck(strncmp(input.data(), output.data(), strlen(first.data())) == 0);
}