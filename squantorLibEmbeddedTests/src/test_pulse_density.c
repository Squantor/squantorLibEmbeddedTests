/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2022 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
#include <MinUnit.h>
#include <pulse_density.h>

MINUNIT_ADD(testPulseDensityInit, NULL, NULL) {
  pulseDensityModulator DUT;
  pulseDensityInit(&DUT, 1000, 100);
  minUnitCheck(DUT.sum == 0);
  minUnitCheck(DUT.step == 100);
  minUnitCheck(DUT.threshold == 1000);
}

MINUNIT_ADD(testPulseDensityOutput, NULL, NULL) {
  pulseDensityModulator DUT;
  pulseDensityInit(&DUT, 1000, 99);
  minUnitCheck(pulseDensityOutput(&DUT) == false);
  minUnitCheck(DUT.sum == 99);
  for (int i = 0; i < 9; i++) {
    minUnitCheck(pulseDensityOutput(&DUT) == false);
  }
  minUnitCheck(DUT.sum == 990);
  minUnitCheck(pulseDensityOutput(&DUT) == true);
  minUnitCheck(DUT.sum == 89);
}