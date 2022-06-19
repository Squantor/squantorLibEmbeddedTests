/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2022 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * \file test_rmw.cpp
 *
 * Read Modify Write tests
 */

#include <MinUnit.h>
#include <string.h>
#include <stdint.h>
#include <bitblit.hpp>

MINUNIT_ADD(testReadModifyWrite, NULL, NULL) {
  uint8_t testSource = 0x00;
  uint8_t testDestination = 0x00;
  // test AND
  testSource = 0xAA;
  testDestination = 0xCC;
  util::readModifyWrite(&testDestination, &testSource, 0x0F, 0, util::bitblitOperation::OP_AND);
  minUnitCheck(testDestination == 0xC8);
  // test MOV
  testSource = 0xF;
  testDestination = 0x00;
  util::readModifyWrite(&testDestination, &testSource, 0x3C, 2, util::bitblitOperation::OP_MOV);
  minUnitCheck(testDestination == 0x3C);
  testSource = 0xF0;
  testDestination = 0x00;
  util::readModifyWrite(&testDestination, &testSource, 0x3C, -2, util::bitblitOperation::OP_MOV);
  minUnitCheck(testDestination == 0x3C);
  testSource = 0x0F;
  testDestination = 0x01;
  util::readModifyWrite(&testDestination, &testSource, 0x3C, 2, util::bitblitOperation::OP_MOV);
  minUnitCheck(testDestination == 0x3D);
  testSource = 0x0F;
  testDestination = 0x91;
  util::readModifyWrite(&testDestination, &testSource, 0x3C, 2, util::bitblitOperation::OP_MOV);
  minUnitCheck(testDestination == 0xBD);
  testSource = 0x02;
  testDestination = 0x81;
  util::readModifyWrite(&testDestination, &testSource, 0x03, 0, util::bitblitOperation::OP_MOV);
  minUnitCheck(testDestination == 0x82);
  // test NOT
  testSource = 0xF;
  testDestination = 0xFF;
  util::readModifyWrite(&testDestination, &testSource, 0x3C, 2, util::bitblitOperation::OP_NOT);
  minUnitCheck(testDestination == 0xC3);
  testSource = 0xF0;
  testDestination = 0x0F;
  util::readModifyWrite(&testDestination, &testSource, 0x3C, -2, util::bitblitOperation::OP_NOT);
  minUnitCheck(testDestination == 0x03);
  // test OR
  testSource = 0xAA;
  testDestination = 0xCC;
  util::readModifyWrite(&testDestination, &testSource, 0xF0, 4, util::bitblitOperation::OP_OR);
  minUnitCheck(testDestination == 0xEC);
  // test XOR
  testSource = 0xAA;
  testDestination = 0xCC;
  util::readModifyWrite(&testDestination, &testSource, 0xF0, 4, util::bitblitOperation::OP_XOR);
  minUnitCheck(testDestination == 0x6C);
}