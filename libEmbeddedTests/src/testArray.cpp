/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2020-2020 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
#include <testArray.hpp>
#include <MinUnit.hpp>

MU_TEST_TEST_STATE;

static void arrayTestSetup(void)
{

}

static void arrayTestTeardown(void)
{

}

MU_TEST(testConstructor)
{
    mu_check(true == true);
}

MU_TEST_SUITE(arrayTests)
{
    MU_SUITE_CONFIGURE(&arrayTestSetup, &arrayTestTeardown);
    MU_RUN_TEST(testConstructor);
}

void executeArrayTests(void)
{
    MU_RUN_SUITE(arrayTests);
}