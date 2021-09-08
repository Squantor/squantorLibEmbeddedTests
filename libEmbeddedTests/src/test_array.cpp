/*
SPDX-License-Identifier: MIT

Copyright (c) 2020-2020 Bart Bilos
For conditions of distribution and use, see LICENSE file
 */

/** \file testArray.cpp

\brief Tests for util::array
 
Tests for util::array
*/
#include <MinUnit.h>
#include <array.hpp>


/** \brief util::array test size()

testing the util::array size method
*/
MINUNIT_ADD(testArraySize, NULL, NULL)
{
    util::array<int, 10> testNonEmptyArray {0,1,2,3,4,5,6,7,8,9};
    minUnitCheck(testNonEmptyArray.size() == 10);

    util::array<int, 0> testEmptyArray;
    minUnitCheck(testEmptyArray.size() == 0);
}

/** \brief util::array test empty()

testing the util::array empty method
 */
MINUNIT_ADD(testArrayEmpty, NULL, NULL)
{
    util::array<int, 10> testNonEmptyArray {0,1,2,3,4,5,6,7,8,9};
    minUnitCheck(testNonEmptyArray.empty() == false);

    util::array<int, 0> testEmptyArray;
    minUnitCheck(testEmptyArray.empty() == true);
}

/** \brief util::array test data()

testing the util::array data method
*/
MINUNIT_ADD(testArrayData, NULL, NULL)
{
    util::array<int, 10> testData {0,1,2,3,4,5,6,7,8,9};
    minUnitCheck(testData.data() != nullptr);
    util::array<int, 10> const testConstData {0,1,2,3,4,5,6,7,8,9};
    minUnitCheck(testConstData.data() != nullptr);

}

/** \brief util::array test indexing operator

testing the util::array array indexing operator
*/
MINUNIT_ADD(testArrayIndexing, NULL, NULL)
{
    util::array<int, 10> testIndexing {0,1,2,3,4,5,6,7,8,9};
    minUnitCheck(testIndexing[0] == 0);
    minUnitCheck(testIndexing[3] == 3);
    util::array<int, 10> const testConstIndexing {0,1,2,3,4,5,6,7,8,9};
    minUnitCheck(testConstIndexing[1] == 1);
    minUnitCheck(testConstIndexing[5] == 5);
}

/** \brief util::array test front method

testing the util::array front method for retrieving the first element
*/
MINUNIT_ADD(testArrayFront, NULL, NULL)
{
    util::array<int, 5> testFront {42,1,2,3,4};
    minUnitCheck(testFront.front() == 42);
    util::array<int, 1> const testConstFront {55};
    minUnitCheck(testConstFront.front() == 55);
}

/** \brief util::array test back method

testing the util::array back method for retrieving the last element
*/
MINUNIT_ADD(testArrayBack, NULL, NULL)
{
    util::array<int, 5> testBack {42,1,2,3,22};
    minUnitCheck(testBack.back() == 22);
    util::array<int, 3> const testConstBack {42, 0, 43};
    minUnitCheck(testConstBack.back() == 43);
}

/** \brief util::array test begin method

testing the util::array begin method for getting a pointer to the first element
*/
MINUNIT_ADD(testArrayBegin, NULL, NULL)
{
    util::array<int, 5> testBegin {42,1,2,3,22};
    int *testBeginData = testBegin.data();
    minUnitCheck(testBegin.begin() == testBeginData);
    minUnitCheck(*(testBegin.begin()) == 42);
    util::array<int, 3> const testConstBegin {52, 0, 43};
    const int *testConstBeginData = testConstBegin.data();
    minUnitCheck(testConstBegin.begin() == testConstBeginData);
    minUnitCheck(*(testConstBegin.begin()) == 52);
}

/** \brief util::array test end method

testing the util::array end method for getting a pointer beyond the last element
*/
MINUNIT_ADD(testArrayEnd, NULL, NULL)
{
    util::array<int, 5> testEnd {42,1,2,3,22};
    int *testEndData = testEnd.data();
    minUnitCheck(testEnd.end() == &testEndData[5]);
    util::array<int, 3> const testConstEnd {52, 0, 43};
    const int *testConstEndData = testConstEnd.data();
    minUnitCheck(testConstEnd.end() == &testConstEndData[3]);
}

/** \brief test out a rangeloop

testing the util::array end method for getting a pointer beyond the last element
*/
MINUNIT_ADD(testArrayRangeLoop, NULL, NULL)
{
    util::array<int, 5> testRangeLoop {1,2,3,4,5};
    int sum = 0;
    for(const int& a : testRangeLoop)
    {
        sum += a;
    }
    minUnitCheck(sum == 15);
}

/** \brief test out a const rangeloop

*/
MINUNIT_ADD(testArrayConstRangeLoop, NULL, NULL)
{
    const util::array<int, 5> testRangeLoop {1,2,3,4,5};
    int sum = 0;
    for(const int& a : testRangeLoop)
    {
        sum += a;
    }
    minUnitCheck(sum == 15);
}