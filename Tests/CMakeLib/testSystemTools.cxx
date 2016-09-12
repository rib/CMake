/*============================================================================
  CMake - Cross Platform Makefile Generator
  Copyright 2000-2011 Kitware, Inc., Insight Software Consortium

  Distributed under the OSI-approved BSD License (the "License");
  see accompanying file Copyright.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the License for more information.
============================================================================*/
#include "cmSystemTools.h"

#include <iostream>
#include <string>

#define cmPassed(m) std::cout << "Passed: " << (m) << "\n"
#define cmFailed(m)                                                           \
  std::cout << "FAILED: " << (m) << "\n";                                     \
  failed = 1

int testSystemTools(int /*unused*/, char* /*unused*/ [])
{
  int failed = 0;
  // ----------------------------------------------------------------------
  // Test cmSystemTools::UpperCase
  std::string str = "abc";
  std::string strupper = "ABC";
  if (cmSystemTools::UpperCase(str) == strupper) {
    cmPassed("cmSystemTools::UpperCase is working");
  } else {
    cmFailed("cmSystemTools::UpperCase is working");
  }

  // ----------------------------------------------------------------------
  // Test cmSystemTools::strverscmp
  if (cmSystemTools::strverscmp("", "") != 0) {
    // empty string
    cmFailed("cmSystemTools::strverscmp error empty string");
  }
  if (cmSystemTools::strverscmp("lib_1.1.0", "") < 0) {
    // empty string goes first
    cmFailed("cmSystemTools::strverscmp error empty string goes first");
  }
  if (cmSystemTools::strverscmp("abc", "ab") < 0) {
    // shortest goes first
    cmFailed("cmSystemTools::strverscmp shortest non digit");
  }
  if (cmSystemTools::strverscmp("12345", "123") < 0) {
    // only numbers
    cmFailed("cmSystemTools::strverscmp error only numbers");
  }
  if (cmSystemTools::strverscmp("12345", "00345") <
      0) { // only numbers, same length
    cmFailed("cmSystemTools::strverscmp error only numbers, same length");
  }
  if (cmSystemTools::strverscmp("12abcde", "12abcc") <= 0) {
    cmFailed("cmSystemTools::strverscmp  standard order");
  }
  if (cmSystemTools::strverscmp("lib_1.10.0", "lib_1.1.0") < 0) {
    // symmetric
    cmFailed("cmSystemTools::strverscmp error /symmetric");
  }
  if (cmSystemTools::strverscmp("lib_1.1.0", "lib_1.001.000") <
      0) { // multiple zeros
    cmFailed("cmSystemTools::strverscmp error multiple zeros");
  }
  if (cmSystemTools::strverscmp("lib_1.2_2", "lib_1.2_10") >=
      0) { // last number
    cmFailed("cmSystemTools::strverscmp error last number");
  }
  if (cmSystemTools::strverscmp("lib", "lib") != 0) {
    // same string
    cmFailed("cmSystemTools::strverscmp error same string");
  }
  if (cmSystemTools::strverscmp("2lib", "21lib") >= 0) {
    // suffix letter
    cmFailed("cmSystemTools::strverscmp suffix letter");
  }
  if (cmSystemTools::strverscmp("002lib", "02lib") >= 0) {
    // suffix letter decimal
    cmFailed("cmSystemTools::strverscmp suffix letter decimal");
  }
  if (cmSystemTools::strverscmp("9a", "10") >= 0) {
    // letter filler
    cmFailed("cmSystemTools::strverscmp error letter filler");
  }
  if (cmSystemTools::strverscmp("01", "010") >= 0) {
    // decimal comparison
    cmFailed("cmSystemTools::strverscmp errordecimal comparison");
  }
  if (cmSystemTools::strverscmp("01", "0") >= 0) {
    // zero and decimal
    cmFailed("cmSystemTools::strverscmp error zero and decimal");
  }
  if (cmSystemTools::strverscmp("000", "00") >= 0) {
    // zero and decimal
    cmFailed("cmSystemTools::strverscmp error zero and decimal");
  }
  if (cmSystemTools::strverscmp("000", "0001") < 0) {
    // zero and decimal
    cmFailed("cmSystemTools::strverscmp leading zeros");
  }

  // test sorting using standard strvercmp input
  std::vector<std::string> testString;
  testString.push_back("000");
  testString.push_back("00");
  testString.push_back("01");
  testString.push_back("010");
  testString.push_back("09");
  testString.push_back("0");
  testString.push_back("1");
  testString.push_back("9");
  testString.push_back("10");

  // test global ordering of input strings
  for (size_t i = 0; i < testString.size() - 1; i++) {
    for (size_t j = i + 1; j < testString.size(); j++) {
      if (cmSystemTools::strverscmp(testString[i], testString[j]) >= 0) {
        cmFailed("cmSystemTools::strverscmp error in comparing strings " +
                 testString[i] + " " + testString[j]);
      }
    }
  }

  if (!failed) {
    cmPassed("cmSystemTools::strverscmp working");
  }
  return failed;
}
