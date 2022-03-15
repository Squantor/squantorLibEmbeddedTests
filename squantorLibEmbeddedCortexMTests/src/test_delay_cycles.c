/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2022 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
#include <mcu_ll.h>
#include <MinUnit.h>
#include <delay_cycles.h>

MINUNIT_ADD(testDelayCoucles, NULL, NULL) {
  uint32_t startVal, endVal, delta;
  // systick should be running, otherwise we cant time
  // set systick to a high value so we can count down without being afraid of overflows
  startVal = SysTick->VAL;
  delay_cycles(100);
  endVal = SysTick->VAL;
  delta = startVal - endVal;
  minUnitCheck(delta == 150u);
  startVal = SysTick->VAL;
  delay_cycles(1000);
  endVal = SysTick->VAL;
  delta = startVal - endVal;
  minUnitCheck(delta == 1054u);
  startVal = SysTick->VAL;
  delay_cycles(10000);
  endVal = SysTick->VAL;
  delta = startVal - endVal;
  minUnitCheck(delta == 10054u);
}
