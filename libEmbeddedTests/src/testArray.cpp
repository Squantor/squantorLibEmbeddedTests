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

/** \brief util::array test back method

testing the util::array back method for retrieving the last element
*/
MU_TEST(testArrayBack)
{
    util::array<int, 5> testBack {42,1,2,3,22};
    mu_check(testBack.back() == 22);
    util::array<int, 3> const testConstBack {42, 0, 43};
    mu_check(testConstBack.back() == 43);
}

/** \brief util::array test begin method

testing the util::array begin method for getting a pointer to the first element
*/
MU_TEST(testArrayBegin)
{
    util::array<int, 5> testBegin {42,1,2,3,22};
    int *testBeginData = testBegin.data();
    mu_check(testBegin.begin() == testBeginData);
    mu_check(*(testBegin.begin()) == 42);
    util::array<int, 3> const testConstBegin {52, 0, 43};
    const int *testConstBeginData = testConstBegin.data();
    mu_check(testConstBegin.begin() == testConstBeginData);
    mu_check(*(testConstBegin.begin()) == 52);
}

/** \brief util::array test end method

testing the util::array end method for getting a pointer beyond the last element
*/
MU_TEST(testArrayEnd)
{
    util::array<int, 5> testEnd {42,1,2,3,22};
    int *testEndData = testEnd.data();
    mu_check(testEnd.end() == &testEndData[5]);
    util::array<int, 3> const testConstEnd {52, 0, 43};
    const int *testConstEndData = testConstEnd.data();
    mu_check(testConstEnd.end() == &testConstEndData[3]);
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
    MU_RUN_TEST(testArrayBack);
    MU_RUN_TEST(testArrayBegin);
    MU_RUN_TEST(testArrayEnd);
}

/** \brief execute tests for util::array

Entry point for executing all the tests for the util::array datastructure defined in libEmbedded.
*/
void executeArrayTests(void)
{
    MU_RUN_SUITE(arrayTests);
}