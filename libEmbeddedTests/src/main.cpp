/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2020-2020 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
#include <stdio.h>
#include <iostream>
#include <MinUnit.hpp>
#include <testArray.hpp>

int minunitRun; /* tests run */
int minunitFailures; /* tests failed */
int minunitAsserts; /* asserts run */

/**
 * Program entry point
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