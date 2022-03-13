/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2022 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
#include <MinUnit.h>
#include <pulse_density.hpp>

MINUNIT_ADD(testPulseDensityModulator, NULL, NULL) {
  util::PulseDensityModulator DUT(1000, 99);
  minUnitCheck(DUT.sum == 0);
  minUnitCheck(DUT.step == 99);
  minUnitCheck(DUT.threshold == 1000);
  minUnitCheck(DUT.output() == false);
  minUnitCheck(DUT.sum == 99);
  for (int i = 0; i < 9; i++) {
    minUnitCheck(DUT.output() == false);
  }
  minUnitCheck(DUT.sum == 990);
  minUnitCheck(DUT.output() == true);
  minUnitCheck(DUT.sum == 89);
}