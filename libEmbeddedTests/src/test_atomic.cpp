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


/** \brief util::atomic test uint16_t atomics */
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

/** \brief util::atomic test int atomics */
MINUNIT_ADD(testAtomicInt)
{
    util::atomic<int> Dut {0};
    minUnitCheck(Dut.load() == 0);
    Dut = 1;
    minUnitCheck(Dut.load() == 1);
    Dut++;
    minUnitCheck(Dut.load() == 2);
    Dut--;
    minUnitCheck(Dut.load() == 1);
    Dut = Dut + 1;
    minUnitCheck(Dut.load() == 2);
    Dut = Dut - 1;
    minUnitCheck(Dut.load() == 1);
    int old = Dut.exchange(5);
    minUnitCheck(Dut.load() == 5);
    minUnitCheck(old == 1);
    int expected = 6;
    minUnitCheck(Dut.compare_exchange_weak(expected, 7) == false);
    minUnitCheck(Dut.load() == 5);
    expected = 5;
    minUnitCheck(Dut.compare_exchange_weak(expected, 7) == true);
    minUnitCheck(Dut.load() == 7);
}

/** \brief util::atomic test uint8_t atomics */
MINUNIT_ADD(testAtomicUint8)
{
    util::atomic<uint8_t> Dut {0u};
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
    Dut = 0xF0;
    Dut = Dut & 0x33;
    minUnitCheck(Dut.load() == 0x30);
    Dut = Dut | 0xF3;
    minUnitCheck(Dut.load() == 0xF3);
    Dut = Dut ^ 0x37;
    minUnitCheck(Dut.load() == 0xC4);
    uint8_t old = Dut.exchange(0x12);
    minUnitCheck(Dut.load() == 0x12);
    minUnitCheck(old == 0xC4);
    uint8_t expected = 0x13;
    minUnitCheck(Dut.compare_exchange_weak(expected, 0x14) == false);
    minUnitCheck(Dut.load() == 0x12);
    expected = 0x12;
    minUnitCheck(Dut.compare_exchange_weak(expected, 0x14) == true);
    minUnitCheck(Dut.load() == 0x14);
}