/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2022 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/* 
 * \brief main entrypoint of squantorLibEmbedded routines for Cortex M processors
 */
#include <generic_board.hpp>
#include <MinUnit.h>

volatile unsigned int systicks = 0;

extern "C" {
void SysTick_Handler(void) {
  systicks = systicks + 1;
}
}

/** \brief overridden reporting function
 *
 * Executes the minunit test framework and checks the results
 */
void minunitReport(const char* message) {}

/**
 * \brief Program entry point
 *
 * Program entry point, execution starts here. Any unittest initialisation happens here.
 *
 * \return returns the error code to the operating system
 */
int main() {
  boardInit();
  minunitRun();
  if (minunitTestState.failures == 0)
    __BKPT(0);
  else
    __BKPT(1);
  while (1) {
    __NOP();
  }
}
