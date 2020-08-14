/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2020-2020 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/** 
 * \file testArray.cpp
 * 
 * \brief Tests for util::array
 * 
 * Tests for util::array
 */
#include <testArray.hpp>
#include <MinUnit.hpp>
#include <array.hpp>

MU_TEST_TEST_STATE; /** Test suite local state */


/** 
 * \brief util::array setup
 * 
 * util::array setup
 * 
 */
static void arrayTestSetup(void)
{

}

/** 
 * \brief util::array teardown
 * 
 * util::array teardown
 * 
 */
static void arrayTestTeardown(void)
{

}

/** 
 * \brief util::array constructor test
 * 
 * util::array constructor test
 * 
 */
MU_TEST(testArraySize)
{
    util::array<int, 10> testArray = {0,1,2,3,4,5,6,7,8,9};
    volatile size_t arraysize = testArray.size();
    mu_check(testArray.size() == 10);
}

/** 
 * \brief util::array test suite
 * 
 * util::array test suite
 * 
 */
MU_TEST_SUITE(arrayTests)
{
    MU_SUITE_CONFIGURE(&arrayTestSetup, &arrayTestTeardown);
    MU_RUN_TEST(testArraySize);
}

/**
 * \brief execute tests for util::array
 * 
 * Entry point for executing all the tests for the util::array 
 * 
 * datastructure defined in libEmbedded.
 */
void executeArrayTests(void)
{
    MU_RUN_SUITE(arrayTests);
}