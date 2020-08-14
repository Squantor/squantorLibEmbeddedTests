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
MU_TEST(testConstructor)
{
    mu_check(true == true);
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
    MU_RUN_TEST(testConstructor);
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