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
  temp = util::appendDigit(temp, 0xAu);
  temp = util::appendDigit(temp, 0xCu);
  temp = util::appendDigit(temp, 0xFu);
  minUnitCheck(strncmp(input.data(), output.data(), strlen(output.data())) == 0);
}

MINUNIT_ADD(testFormatAppendHex, nullptr, nullptr) {
  std::array<char, 32> input;
  std::array<char, 32> output{"0123456789ABCDEF"};
  std::span<char> temp = input;
  temp = util::appendHex(temp, static_cast<std::uint32_t>(0x01234567));
  temp = util::appendHex(temp, static_cast<std::uint32_t>(0x89ABCDEF));
  minUnitCheck(strncmp(input.data(), output.data(), strlen(output.data())) == 0);
  temp = input;
  temp = util::appendHex(temp, static_cast<std::uint16_t>(0x0123));
  temp = util::appendHex(temp, static_cast<std::uint16_t>(0x4567));
  temp = util::appendHex(temp, static_cast<std::uint16_t>(0x89ab));
  temp = util::appendHex(temp, static_cast<std::uint16_t>(0xcdef));
  minUnitCheck(strncmp(input.data(), output.data(), strlen(output.data())) == 0);
  temp = input;
  temp = util::appendHex(temp, static_cast<std::uint8_t>(0x01));
  temp = util::appendHex(temp, static_cast<std::uint8_t>(0x23));
  temp = util::appendHex(temp, static_cast<std::uint8_t>(0x45));
  temp = util::appendHex(temp, static_cast<std::uint8_t>(0x67));
  temp = util::appendHex(temp, static_cast<std::uint8_t>(0x89));
  temp = util::appendHex(temp, static_cast<std::uint8_t>(0xab));
  temp = util::appendHex(temp, static_cast<std::uint8_t>(0xcd));
  temp = util::appendHex(temp, static_cast<std::uint8_t>(0xef));
  minUnitCheck(strncmp(input.data(), output.data(), strlen(output.data())) == 0);
}

MINUNIT_ADD(testFormatAppenDec, nullptr, nullptr) {
  std::array<char, 12> input;
  std::array<char, 11> outputUnsigned{"4294967295"};
  std::array<char, 12> outputSigned32{"-2147483648"};
  std::array<char, 12> outputSigned16{"-3276832767"};
  std::array<char, 12> outputSigned8{"-12812701"};

  std::span<char> temp = input;
  temp = util::appendDec(temp, static_cast<std::uint32_t>(4294967295u));
  minUnitCheck(strncmp(input.data(), outputUnsigned.data(), strlen(outputUnsigned.data())) == 0);
  temp = input;
  temp = util::appendDec(temp, static_cast<std::uint16_t>(42949u));
  temp = util::appendDec(temp, static_cast<std::uint16_t>(6729u));
  temp = util::appendDec(temp, static_cast<std::uint16_t>(5u));
  minUnitCheck(strncmp(input.data(), outputUnsigned.data(), strlen(outputUnsigned.data())) == 0);
  temp = input;
  temp = util::appendDec(temp, static_cast<std::uint8_t>(42u));
  temp = util::appendDec(temp, static_cast<std::uint8_t>(94u));
  temp = util::appendDec(temp, static_cast<std::uint8_t>(96u));
  temp = util::appendDec(temp, static_cast<std::uint8_t>(72u));
  temp = util::appendDec(temp, static_cast<std::uint8_t>(95u));
  minUnitCheck(strncmp(input.data(), outputUnsigned.data(), strlen(outputUnsigned.data())) == 0);
  temp = input;
  temp = util::appendDec(temp, static_cast<std::int32_t>(-2147483648));
  minUnitCheck(strncmp(input.data(), outputSigned32.data(), strlen(outputSigned32.data())) == 0);
  temp = input;
  temp = util::appendDec(temp, static_cast<std::int16_t>(-32768));
  temp = util::appendDec(temp, static_cast<std::int16_t>(32767));
  minUnitCheck(strncmp(input.data(), outputSigned16.data(), strlen(outputSigned16.data())) == 0);
  temp = input;
  temp = util::appendDec(temp, static_cast<std::int8_t>(-128));
  temp = util::appendDec(temp, static_cast<std::int8_t>(127));
  temp = util::appendDec(temp, static_cast<std::int8_t>(0));
  temp = util::appendDec(temp, static_cast<std::int8_t>(1));
  minUnitCheck(strncmp(input.data(), outputSigned8.data(), strlen(outputSigned8.data())) == 0);
}
