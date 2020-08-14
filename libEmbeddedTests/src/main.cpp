/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2020-2020 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */

/** 
 * \file main.cpp
 * 
 * Main program entry point
 * 
 * Program execution starts here in main().
 */ 
#include <stdio.h>
#include <iostream>
#include <MinUnit.hpp>
#include <testArray.hpp>

MU_TEST_GLOBAL_STATE;    /** Global test state */

/**
 * \brief Program entry point
 * 
 * Program entry point, execution starts here. Any unittest initialisation happens here.
 * 
 * \return returns the error code to the operating system
 */
int main()
{
    executeArrayTests();
    printf("Tests run: %d\n", minunitRun);
    printf("Tests failed: %d\n", minunitFailures);
    printf("Checks executed: %d\n", minunitAsserts);
    if(minunitFailures == 0)
        return 0;
    else
        return -1;   
}