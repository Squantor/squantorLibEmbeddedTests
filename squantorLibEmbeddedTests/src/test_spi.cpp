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
#include <array>
#include <hardware_mocks.hpp>

util::hardware_mocks::spi<100, util::hardware_mocks::spiChipEnables> testSpiPeripheral;

static void testGenericSpiSetup(minunitState* testResults) {
  testSpiPeripheral.initialize();
  minUnitPass();
}

static void testGenericSpiTeardown(minunitState* testResults) {
  minUnitPass();
}

MINUNIT_ADD(testGenericSpiTransmit, testGenericSpiSetup, testGenericSpiTeardown) {
  std::array<uint16_t, 10> testBuf{0x0123, 0x4567, 0x89ab, 0xcdef};
  testSpiPeripheral.transmit(util::hardware_mocks::spiChipEnables::SPI_DEV_0, testBuf.data(), 5, true);
  minUnitCheck(1 == testSpiPeripheral.txTransactionCount());
  minUnitCheck(5 == testSpiPeripheral.txTransactionGetBits(1));
  minUnitCheck(static_cast<uint16_t>(util::hardware_mocks::spiChipEnables::SPI_DEV_0) == testSpiPeripheral.txTransactionGetChip(1));
  minUnitCheck(0 != testSpiPeripheral.txTransactionGetLast(1));
  uint16_t* data = testSpiPeripheral.txTransactionGetData(1);
  minUnitCheck(0x0123 == *data);
  testSpiPeripheral.transmit(util::hardware_mocks::spiChipEnables::SPI_DEV_1, testBuf.data(), 32, false);
  testSpiPeripheral.transmit(util::hardware_mocks::spiChipEnables::SPI_DEV_1, testBuf.data(), 41, true);
  minUnitCheck(3 == testSpiPeripheral.txTransactionCount());
  minUnitCheck(32 == testSpiPeripheral.txTransactionGetBits(2));
  minUnitCheck(static_cast<uint16_t>(util::hardware_mocks::spiChipEnables::SPI_DEV_1) == testSpiPeripheral.txTransactionGetChip(2));
  minUnitCheck(0 == testSpiPeripheral.txTransactionGetLast(2));
  data = testSpiPeripheral.txTransactionGetData(2);
  minUnitCheck(0x89AB == *(data + 2));
  minUnitCheck(41 == testSpiPeripheral.txTransactionGetBits(3));
  minUnitCheck(static_cast<uint16_t>(util::hardware_mocks::spiChipEnables::SPI_DEV_1) == testSpiPeripheral.txTransactionGetChip(3));
  minUnitCheck(0 != testSpiPeripheral.txTransactionGetLast(3));
  data = testSpiPeripheral.txTransactionGetData(3);
  minUnitCheck(0x4567 == *(data + 1));
}

MINUNIT_ADD(testGenericSpiReceive, testGenericSpiSetup, testGenericSpiTeardown) {
  std::array<uint16_t, 10> testBuf{0x0123, 0x4567, 0x89ab, 0xcdef};
  testSpiPeripheral.rxTransactionAdd(util::hardware_mocks::spiChipEnables::SPI_DEV_1, testBuf.data(), 20, true);
  minUnitPass();
}