/*
SPDX-License-Identifier: MIT

Copyright (c) 2020-2020 Bart Bilos
For conditions of distribution and use, see LICENSE file
 */

/** \file testArray.cpp

\brief Tests for util::array
 
Tests for util::array
*/
#include <testArray.hpp>
#include <MinUnit.hpp>
#include <array.hpp>

MU_TEST_TEST_STATE; /** Test suite local state */


/** \brief util::array setup

util::array setup
*/
static void arrayTestSetup(void)
{

}

/** \brief util::array teardown

util::array teardown
*/
static void arrayTestTeardown(void)
{

}

/** \brief util::array test size()

testing the util::array size method
*/
MU_TEST(testArraySize)
{
    util::array<int, 10> testNonEmptyArray {0,1,2,3,4,5,6,7,8,9};
    mu_check(testNonEmptyArray.size() == 10);

    util::array<int, 0> testEmptyArray;
    mu_check(testEmptyArray.size() == 0);
}

/** \brief util::array test empty()

testing the util::array empty method
 */
MU_TEST(testArrayEmpty)
{
    util::array<int, 10> testNonEmptyArray {0,1,2,3,4,5,6,7,8,9};
    mu_check(testNonEmptyArray.empty() == false);

    util::array<int, 0> testEmptyArray;
    mu_check(testEmptyArray.empty() == true);
}

/** \brief util::array test data()

testing the util::array data method
*/
MU_TEST(testArrayData)
{
    util::array<int, 10> testData {0,1,2,3,4,5,6,7,8,9};
    mu_check(testData.data() != nullptr);
    util::array<int, 10> const testConstData {0,1,2,3,4,5,6,7,8,9};
    mu_check(testConstData.data() != nullptr);

}

/** \brief util::array test indexing operator

testing the util::array array indexing operator
*/
MU_TEST(testArrayIndexing)
{
    util::array<int, 10> testIndexing {0,1,2,3,4,5,6,7,8,9};
    mu_check(testIndexing[0] == 0);
    mu_check(testIndexing[3] == 3);
    util::array<int, 10> const testConstIndexing {0,1,2,3,4,5,6,7,8,9};
    mu_check(testConstIndexing[1] == 1);
    mu_check(testConstIndexing[5] == 5);
}

/** \brief util::array test front method

testing the util::array front method for retrieving the first element
*/
MU_TEST(testArrayFront)
{
    util::array<int, 5> testFront {42,1,2,3,4};
    mu_check(testFront.front() == 42);
    util::array<int, 1> const testConstFront {55};
    mu_check(testConstFront.front() == 55);
}

/** \brief util::array test suite

util::array test suite
*/
MU_TEST_SUITE(arrayTests)
{
    MU_SUITE_CONFIGURE(&arrayTestSetup, &arrayTestTeardown);
    MU_RUN_TEST(testArraySize);
    MU_RUN_TEST(testArrayEmpty);
    MU_RUN_TEST(testArrayData);
    MU_RUN_TEST(testArrayIndexing);
    MU_RUN_TEST(testArrayFront);
}

/** \brief execute tests for util::array

Entry point for executing all the tests for the util::array datastructure defined in libEmbedded.
*/
void executeArrayTests(void)
{
    MU_RUN_SUITE(arrayTests);
}