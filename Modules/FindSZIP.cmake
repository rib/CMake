#.rst:
# FindSZIP
# ---------
#
# Find SZIP, a compression library developed by HDF5.
#
# Once done this will define
#
# ::
#   SZIP_FOUND - System has SZIP
#   SZIP_INCLUDE_DIRS - The SZIP include directories to use
#   SZIP_LIBRARIES - Link these to use SZIP
#   SZIP_VERSION - The version of SZIP found
# ::
#
# The following imported target is also created:
#
# ::
# SZIP::SZIP
# ::
#
# The following variable can be set to guide the search for SZIP libraries and
# includes:
#   SZIP_ROOT_DIR -
#     Search order preference is SZIP_ROOT_DIR followed by ENV{SZIP_INSTALL}.
#     If SZIP_ROOT_DIR is specified then it is searched exclusively, ignoring
#     default search paths.

#=============================================================================
# Copyright 2006-2016 Kitware, Inc.
#
# Distributed under the OSI-approved BSD License (the "License");
# see accompanying file Copyright.txt for details.
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the License for more information.
#=============================================================================
# (To distribute this file outside of CMake, substitute the full
#  License text for the above reference.)

function(_SZIP_get_version)
  set(scratch_dir ${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/szip)
  set(test_file ${scratch_dir}/cmake_szip_version.c)
  file(WRITE ${test_file}
    "#include <stdlib.h>\n"
    "#include <szlib.h>\n"
    "int main(void) {\n"
    "  char const* info_ver = \"INFO\" \":\" SZLIB_VERSION;\n"
    "  return 0;\n"
    "}")
  try_compile(szip_version_test ${scratch_dir} ${test_file}
    CMAKE_FLAGS -DINCLUDE_DIRECTORIES=${SZIP_INCLUDE_DIR}
    COPY_FILE ${scratch_dir}/cmake_szip_version)
  if(szip_version_test)
    file(STRINGS ${scratch_dir}/cmake_szip_version INFO_VER
      REGEX "^INFO:([0-9]+(\\.[0-9]+(\\.[0-9]+)?)?)$")
    string(REGEX MATCH "^INFO:([0-9]+(\\.[0-9]+(\\.[0-9]+)?)?)$"
      INFO_VER "${INFO_VER}")
    set(SZIP_VERSION ${CMAKE_MATCH_1} PARENT_SCOPE)
  endif()
endfunction()

# If the root dir is explicitly specified, then ONLY look there
if(SZIP_ROOT_DIR)
  set(SZIP_SEARCH_OPTS NO_DEFAULT_PATH)
else()
  # Otherwise initialize from an environment variable
  set(SZIP_ROOT_DIR $ENV{SZIP_INSTALL})
endif()

# If we do have a root dir, use it as a hint
if(SZIP_ROOT_DIR)
  set(SZIP_SEARCH_PATHS HINTS ${SZIP_ROOT_DIR})
endif()

# Find the main header
find_path(SZIP_INCLUDE_DIR NAMES szlib.h
  ${SZIP_SEARCH_PATHS} ${SZIP_SEARCH_OPTS}
  PATH_SUFFIXES include include/szip Include Include/szip)

# Find the release library
set(SZIP_LIBRARY_RELEASE_NAMES sz szip)
if(WIN32)
  list(APPEND SZIP_LIBRARY_RELEASE_NAMES libsz libszip)
endif()
find_library(SZIP_LIBRARY_RELEASE NAMES ${SZIP_LIBRARY_RELEASE_NAMES}
  ${SZIP_SEARCH_PATHS} ${SZIP_SEARCH_OPTS}
  PATH_SUFFIXES lib Lib)

# Find the debug library
set(SZIP_LIBRARY_DEBUG_NAMES sz_d szip_d)
if(WIN32)
  list(APPEND SZIP_LIBARY_DEBUG_NAMES libsz_d libszip_d)
endif()
find_library(SZIP_LIBRARY_DEBUG NAMES ${SZIP_LIBRARY_DEBUG_NAMES}
  ${SZIP_SEARCH_PATHS} ${SZIP_SEARCH_OPTS}
  PATH_SUFFIXES lib Lib)

include(SelectLibraryConfigurations)
select_library_configurations(SZIP)

if(SZIP_INCLUDE_DIR AND SZIP_LIBRARY)
  _SZIP_get_version()
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(SZIP
  REQUIRED_VARS SZIP_LIBRARY SZIP_INCLUDE_DIR
  VERSION_VAR   SZIP_VERSION)

# Set up the appropriate import target
if(SZIP_FOUND)
  set(SZIP_LIBRARIES ${SZIP_LIBRARY})
  set(SZIP_INCLUDE_DIRS ${SZIP_INCLUDE_DIR})
  if(NOT TARGET SZIP::SZIP)
    add_library(SZIP::SZIP UNKNOWN IMPORTED)
    set_target_properties(SZIP::SZIP PROPERTIES
      INTERFACE_INCLUDE_DIRECTORIES ${SZIP_INCLUDE_DIR})
    if(SZIP_VERSION)
      set_target_properties(SZIP::SZIP PROPERTIES
        VERSION ${SZIP_VERSION})
    endif()
    if(SZIP_LIBRARY_RELEASE)
      set_target_properties(SZIP::SZIP PROPERTIES
        IMPORTED_LOCATION_RELEASE ${SZIP_LIBRARY_RELEASE})
    endif()
    if(SZIP_LIBRARY_DEBUG)
      set_target_properties(SZIP::SZIP PROPERTIES
        IMPORTED_LOCATION_DEBUG ${SZIP_LIBRARY_DEBUG})
    endif()
  endif()
endif()
