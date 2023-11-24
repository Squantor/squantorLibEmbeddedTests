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
  minUnitCheck(strncmp(input.data(), output.data(), strlen(output.data())) == 0);
}

MINUNIT_ADD(testFormatAppendDigit, nullptr, nullptr) {
  std::array<char, 5> input;
  std::array<char, 5> output{"12AC"};
  std::span<char> temp;
  temp = util::appendDigit(input, 1u);
  temp = util::appendDigit(temp, 2u);
  temp = util::appendDigit(temp, 0xA);
  temp = util::appendDigit(temp, 0xC);
  temp = util::appendDigit(temp, 0xF);
  minUnitCheck(strncmp(input.data(), output.data(), strlen(output.data())) == 0);
}