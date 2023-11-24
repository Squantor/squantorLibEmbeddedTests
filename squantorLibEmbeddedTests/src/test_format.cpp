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
  std::array<char, 15> input;
  std::array<char, 15> output{"firstsecondthi"};
  std::array<char, 6> first{"first"};
  std::array<char, 7> second{"second"};
  std::array<char, 10> third{"third"};
  std::span<char> temp = util::appendString(input, first);
  temp = util::appendString(temp, second);
  temp = util::appendString(temp, third);
  minUnitCheck(strncmp(input.data(), output.data(), strlen(first.data())) == 0);
}