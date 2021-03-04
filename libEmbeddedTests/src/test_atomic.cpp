/*
SPDX-License-Identifier: MIT

Copyright (c) 2021 Bart Bilos
For conditions of distribution and use, see LICENSE file
 */

/** \file testArray.cpp

\brief Tests for util::atomic
 
Tests for util::atomic
*/
#include <MinUnit.h>
#include <stdint.h>
#include <atomic.hpp>


/** \brief util::atomic test size()

testing the util::atomic method
*/
MINUNIT_ADD(testAtomicUint16)
{
    util::atomic<uint16_t> Dut {0u};
    minUnitCheck(Dut.load() == 0u);
    Dut = 1u;
    minUnitCheck(Dut.load() == 1u);
    Dut++;
    minUnitCheck(Dut.load() == 2u);
    Dut--;
    minUnitCheck(Dut.load() == 1u);
    Dut = Dut + 1;
    minUnitCheck(Dut.load() == 2u);
    Dut = Dut - 1;
    minUnitCheck(Dut.load() == 1u);
    Dut = 0xFF00;
    Dut = Dut & 0x0FFF;
    minUnitCheck(Dut.load() == 0x0F00);
    Dut = Dut | 0x05F5;
    minUnitCheck(Dut.load() == 0x0FF5);
    Dut = Dut ^ 0x05F0;
    minUnitCheck(Dut.load() == 0x0A05);
    uint16_t old = Dut.exchange(0x0012);
    minUnitCheck(Dut.load() == 0x0012);
    minUnitCheck(old == 0x0A05);
    uint16_t expected = 0x0013;
    minUnitCheck(Dut.compare_exchange_weak(expected, 0x0014) == false);
    minUnitCheck(Dut.load() == 0x0012);
    expected = 0x0012;
    minUnitCheck(Dut.compare_exchange_weak(expected, 0x0014) == true);
    minUnitCheck(Dut.load() == 0x0014);
    expected = 0x0013;
    minUnitCheck(Dut.compare_exchange_weak(expected, 0x0014) == false);
    minUnitCheck(Dut.load() == 0x0014);
    expected = 0x0014;
    minUnitCheck(Dut.compare_exchange_weak(expected, 0x0012) == true);
    minUnitCheck(Dut.load() == 0x0012);
}