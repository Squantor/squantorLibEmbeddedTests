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
  util::array<uint16_t, 5> testbuf = {0xF0F0, 0xA5A5, 3u, 4u, 5u};
  testSpiPeripheral.transmit(testChipEnables::CHIP_EN_0, testbuf.data(), 9, true);
  minUnitCheck(9 == testRegisters.bits);

}