/*============================================================================
  CMake - Cross Platform Makefile Generator
  Copyright 2000-2016 Kitware, Inc., Insight Software Consortium

  Distributed under the OSI-approved BSD License (the "License");
  see accompanying file Copyright.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the License for more information.
============================================================================*/
#ifndef cmProcessOutput_hxx
#define cmProcessOutput_hxx

#include "cmStandardIncludes.h"

#include <string>
#include <vector>

class cmProcessOutput
{
public:
  static unsigned int defaultCodepage;
  // must match to KWSYSPE_PIPE_BUFFER_SIZE
  cmProcessOutput(unsigned int maxSize = 1024);
  ~cmProcessOutput();
  bool DecodeText(std::string raw, std::string& decoded, size_t id = 0);
  bool DecodeText(const char* data, size_t length, std::string& decoded,
                  size_t id = 0);
  bool DecodeText(std::vector<char> raw, std::vector<char>& decoded,
                  size_t id = 0);

private:
  unsigned int codepage;
  unsigned int bufferSize;
  std::vector<std::string> rawparts;
#if defined(_WIN32)
  bool DoDecodeText(std::string raw, std::string& decoded, wchar_t* lastChar);
#endif
};

#endif
