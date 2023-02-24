/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2023 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 *  \file test_spi.cpp
 *  Tests for generic SPI class/driver
 */
#include <MinUnit.h>
#include <spi.hpp>

enum class testChipEnables : uint32_t {
  CHIP_EN_0 = 0,
  CHIP_EN_1 = 1,
};

util::spi::PC::registers<100> testRegisters;
util::spi::PC::spiPeripheral<testRegisters, testChipEnables> testSpiPeripheral;

static void testGenericSpiDriverSetup(minunitState *testResults) {
  // minUnitPass();  // supress warning
  testSpiPeripheral.init();
  minUnitCheck(0u == testRegisters.bits);
  minUnitCheck(0u == testRegisters.data[0]);
}

static void testGenericSpiDriverTeardown(minunitState *testResults) {
  minUnitPass();  // supress warning
}

MINUNIT_ADD(testGenericSpiDriverTransmit, testGenericSpiDriverSetup, testGenericSpiDriverTeardown) {
  util::array<uint16_t, 5> testbuf = {0x55FF, 0xA5A5, 3u, 4u, 5u};
  testSpiPeripheral.transmit(testChipEnables::CHIP_EN_0, testbuf.data(), 9, true);
  minUnitCheck(9 == testRegisters.bits);
  minUnitCheck(0x1FF == testRegisters.data[0]);
  minUnitCheck(0x0 == testRegisters.data[1]);
  testSpiPeripheral.transmit(testChipEnables::CHIP_EN_0, testbuf.data(), 16, true);
  minUnitCheck(16 == testRegisters.bits);
  minUnitCheck(0x55FF == testRegisters.data[0]);
  minUnitCheck(0x0 == testRegisters.data[1]);
  testbuf[0] = 0x1234;
  testSpiPeripheral.transmit(testChipEnables::CHIP_EN_0, testbuf.data(), 20, true);
  minUnitCheck(20 == testRegisters.bits);
  minUnitCheck(0x1234 == testRegisters.data[0]);
  minUnitCheck(0x5 == testRegisters.data[1]);
  testSpiPeripheral.transmit(testChipEnables::CHIP_EN_0, testbuf.data(), 28, true);
  minUnitCheck(28 == testRegisters.bits);
  minUnitCheck(0x1234 == testRegisters.data[0]);
  minUnitCheck(0x5A5 == testRegisters.data[1]);
}