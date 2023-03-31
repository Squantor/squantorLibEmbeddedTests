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
#include <span>
#include <cstdint>
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
  testSpiPeripheral.transmit(util::hardware_mocks::spiChipEnables::SPI_DEV_0, testBuf, 5, true);
  minUnitCheck(1 == testSpiPeripheral.txTransactionCount());
  minUnitCheck(5 == testSpiPeripheral.txTransactionGetBits(1));
  minUnitCheck(static_cast<uint16_t>(util::hardware_mocks::spiChipEnables::SPI_DEV_0) == testSpiPeripheral.txTransactionGetChip(1));
  minUnitCheck(0 != testSpiPeripheral.txTransactionGetLast(1));
  uint16_t* data = testSpiPeripheral.txTransactionGetData(1);
  minUnitCheck(0x0123 == *data);
  testSpiPeripheral.transmit(util::hardware_mocks::spiChipEnables::SPI_DEV_1, testBuf, 32, false);
  testSpiPeripheral.transmit(util::hardware_mocks::spiChipEnables::SPI_DEV_1, testBuf, 41, true);
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
  std::array<uint16_t, 10> receiveBuf;
  testSpiPeripheral.rxTransactionAdd(util::hardware_mocks::spiChipEnables::SPI_DEV_1, testBuf, 20, true);
  minUnitCheck(1 == testSpiPeripheral.rxTransactionCount());
  receiveBuf.fill(0);
  testSpiPeripheral.receive(util::hardware_mocks::spiChipEnables::SPI_DEV_1, receiveBuf, 20, true);
  minUnitCheck(util::hardware_mocks::spiErrors::noError == testSpiPeripheral.spiError);
  minUnitCheck(receiveBuf[0] == testBuf[0]);
  minUnitCheck(receiveBuf[1] == testBuf[1]);
  minUnitCheck(0 == receiveBuf[2]);
  testSpiPeripheral.rxTransactionAdd(util::hardware_mocks::spiChipEnables::SPI_DEV_2, testBuf, 8, false);
  testSpiPeripheral.rxTransactionAdd(util::hardware_mocks::spiChipEnables::SPI_DEV_2, testBuf, 35, true);
  minUnitCheck(3 == testSpiPeripheral.rxTransactionCount());
  receiveBuf.fill(0);
  testSpiPeripheral.receive(util::hardware_mocks::spiChipEnables::SPI_DEV_2, receiveBuf, 8, false);
  minUnitCheck(util::hardware_mocks::spiErrors::noError == testSpiPeripheral.spiError);
  minUnitCheck(receiveBuf[0] == testBuf[0]);
  minUnitCheck(0 == receiveBuf[1]);
  receiveBuf.fill(0);
  testSpiPeripheral.receive(util::hardware_mocks::spiChipEnables::SPI_DEV_2, receiveBuf, 34, true);
  minUnitCheck(util::hardware_mocks::spiErrors::mismatch == testSpiPeripheral.spiError);
  testSpiPeripheral.spiError = util::hardware_mocks::spiErrors::noError;
  testSpiPeripheral.receive(util::hardware_mocks::spiChipEnables::SPI_DEV_2, receiveBuf, 35, true);
  minUnitCheck(util::hardware_mocks::spiErrors::noError == testSpiPeripheral.spiError);
  minUnitCheck(receiveBuf[0] == testBuf[0]);
  minUnitCheck(receiveBuf[1] == testBuf[1]);
}

MINUNIT_ADD(testGenericSpiTransceive, testGenericSpiSetup, testGenericSpiTeardown) {
  std::array<uint16_t, 10> txBuf{0x0123, 0x4567, 0x89ab, 0xcdef};
  uint16_t* txResultBuf;
  std::array<uint16_t, 10> rxBuf{0x0123, 0x4567, 0x89ab, 0xcdef};
  std::array<uint16_t, 10> rxResultBuf;
  testSpiPeripheral.rxTransactionAdd(util::hardware_mocks::spiChipEnables::SPI_DEV_0, rxBuf, 20, true);
  minUnitCheck(1 == testSpiPeripheral.rxTransactionCount());
  rxResultBuf.fill(0);
  testSpiPeripheral.transceive(util::hardware_mocks::spiChipEnables::SPI_DEV_0, txBuf, rxResultBuf, 20, true);
  minUnitCheck(util::hardware_mocks::spiErrors::noError == testSpiPeripheral.spiError);
  minUnitCheck(rxBuf[0] == rxResultBuf[0]);
  minUnitCheck(rxBuf[1] == rxResultBuf[1]);
  minUnitCheck(0 == rxResultBuf[2]);
  minUnitCheck(1 == testSpiPeripheral.txTransactionCount());
  minUnitCheck(20 == testSpiPeripheral.txTransactionGetBits(1));
  minUnitCheck(static_cast<uint16_t>(util::hardware_mocks::spiChipEnables::SPI_DEV_0) == testSpiPeripheral.txTransactionGetChip(1));
  minUnitCheck(0 != testSpiPeripheral.txTransactionGetLast(1));
  txResultBuf = testSpiPeripheral.txTransactionGetData(1);
  minUnitCheck(0x0123 == txResultBuf[0]);
}
