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

MINUNIT_ADD(testFormatAppendChar, nullptr, nullptr) {
  std::array<char, 8> input;
  std::array<char, 8> output{"18BaZ\n\t"};
  std::span<char> temp = input;
  temp = util::appendChar(temp, '1');
  temp = util::appendChar(temp, '8');
  temp = util::appendChar(temp, 'B');
  temp = util::appendChar(temp, 'a');
  temp = util::appendChar(temp, 'Z');
  temp = util::appendChar(temp, '\n');
  temp = util::appendChar(temp, '\t');
  temp = util::appendChar(temp, '?');
  temp = util::appendChar(temp, '!');
  minUnitCheck(strncmp(input.data(), output.data(), strlen(output.data())) == 0);
}

MINUNIT_ADD(testFormatAppendDigit, nullptr, nullptr) {
  std::array<char, 5> input;
  std::array<char, 5> output{"12AC"};
  std::span<char> temp = input;
  temp = util::appendDigit(temp, 1u);
  temp = util::appendDigit(temp, 2u);
  temp = util::appendDigit(temp, 0xA);
  temp = util::appendDigit(temp, 0xC);
  temp = util::appendDigit(temp, 0xF);
  minUnitCheck(strncmp(input.data(), output.data(), strlen(output.data())) == 0);
}

MINUNIT_ADD(testFormatAppendHex, nullptr, nullptr) {
  std::array<char, 32> input;
  std::array<char, 32> output{"0123456789ABCDEF"};
  std::span<char> temp = input;
  temp = util::appendHex(temp, static_cast<uint32_t>(0x01234567));
  temp = util::appendHex(temp, static_cast<uint32_t>(0x89ABCDEF));
  minUnitCheck(strncmp(input.data(), output.data(), strlen(output.data())) == 0);
  temp = input;
  temp = util::appendHex(temp, static_cast<uint16_t>(0x0123));
  temp = util::appendHex(temp, static_cast<uint16_t>(0x4567));
  temp = util::appendHex(temp, static_cast<uint16_t>(0x89ab));
  temp = util::appendHex(temp, static_cast<uint16_t>(0xcdef));
  minUnitCheck(strncmp(input.data(), output.data(), strlen(output.data())) == 0);
  temp = input;
  temp = util::appendHex(temp, static_cast<uint8_t>(0x01));
  temp = util::appendHex(temp, static_cast<uint8_t>(0x23));
  temp = util::appendHex(temp, static_cast<uint8_t>(0x45));
  temp = util::appendHex(temp, static_cast<uint8_t>(0x67));
  temp = util::appendHex(temp, static_cast<uint8_t>(0x89));
  temp = util::appendHex(temp, static_cast<uint8_t>(0xab));
  temp = util::appendHex(temp, static_cast<uint8_t>(0xcd));
  temp = util::appendHex(temp, static_cast<uint8_t>(0xef));
  minUnitCheck(strncmp(input.data(), output.data(), strlen(output.data())) == 0);
}

MINUNIT_ADD(testFormatAppenDec, nullptr, nullptr) {
  std::array<char, 8> input;
  std::array<char, 8> output{"123345"};
  std::span<char> temp = input;
  temp = util::appendDec(temp, static_cast<uint32_t>(123u));
  temp = util::appendDec(temp, static_cast<uint32_t>(345u));
  minUnitCheck(strncmp(input.data(), output.data(), strlen(output.data())) == 0);
  temp = input;
  temp = util::appendDec(temp, static_cast<uint16_t>(12u));
  temp = util::appendDec(temp, static_cast<uint16_t>(3345u));
  minUnitCheck(strncmp(input.data(), output.data(), strlen(output.data())) == 0);
  temp = input;
  temp = util::appendDec(temp, static_cast<uint8_t>(12u));
  temp = util::appendDec(temp, static_cast<uint8_t>(33u));
  temp = util::appendDec(temp, static_cast<uint8_t>(45u));
  minUnitCheck(strncmp(input.data(), output.data(), strlen(output.data())) == 0);
}
