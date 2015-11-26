#.rst:
# CheckCXXSymbolExists
# --------------------
#
# Check if a symbol exists as a function, variable, or macro in C++.
#
# ::
#
#   check_cxx_symbol_exists(<symbol> <files> <variable>)
#
# Check that the ``<symbol>`` is available after including given header
# ``<files>`` and store the result in a ``<variable>``.  Specify the list of
# files in one argument as a semicolon-separated list.
# ``check_cxx_symbol_exists()`` can be used to check in C++ files, as opposed
# to ``check_symbol_exists()``, which works only for C.
#
# If the header files define the symbol as a macro it is considered available
# and assumed to work.  If the header files declare the symbol as a function
# or variable then the symbol must also be available for linking.  If the
# symbol is a type or enum value it will not be recognized (consider using
# :module:`CheckTypeSize` or :module:`CheckCXXSourceCompiles`).
#
# The following variables may be set before calling this macro to modify the
# way the check is run:
#
# ``CMAKE_REQUIRED_FLAGS``
#   String of compile command line flags.
# ``CMAKE_REQUIRED_DEFINITIONS``
#   List of macros to define (-DFOO=bar).
# ``CMAKE_REQUIRED_INCLUDES``
#   List of include directories.
# ``CMAKE_REQUIRED_LIBRARIES``
#   List of libraries to link.
# ``CMAKE_REQUIRED_QUIET``
#   Execute quietly without messages.
#
# ---------------------------------------------------------------------
#
# **Note:** The main difference between this module and the one distributed
# with CMake is that this module supports checking for C++ overloaded
# functions by specifying a comma-separated list of argument types in
# parentheses (note that parentheses are required to be quoted or escaped
# with a backslash in CMake command arguments):
#
# .. code-block:: cmake
#
#    check_cxx_symbol_exists("std::abs(long double)" "cmath" HAVE_STD_ABS_LONG_DOUBLE)
#    check_cxx_symbol_exists("std::pow(long double, long double)" "cmath" HAVE_STD_POW_LONG_DOUBLE)
#
# ``check_cxx_symbol_exists()`` also supports template type argument lists as
# part of the qualified function name or argument type names:
#
# .. code-block:: cmake
#
#    check_cxx_symbol_exists("std::abs(std::complex<long double>)" "complex" HAVE_STD_ABS_COMPLEX_LONG_DOUBLE)
#
# If the function has non-primitive argument types or references an explicit
# template, the header(s) containing the type/template definitions should be
# specified in ``<files>``.
#
# Requires CMake 2.8.12 or later.

#=============================================================================
# Copyright 2003-2011 Kitware, Inc.
# Copyright 2015 Jennifer Yao
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
# * Redistributions of source code must retain the above copyright
#   notice, this list of conditions and the following disclaimer.
#
# * Redistributions in binary form must reproduce the above copyright
#   notice, this list of conditions and the following disclaimer in the
#   documentation and/or other materials provided with the distribution.
#
# * Neither the names of Kitware, Inc., the Insight Software Consortium,
#   nor the names of their contributors may be used to endorse or promote
#   products derived from this software without specific prior written
#   permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
# HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
# LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#=============================================================================

get_filename_component(_CHECK_CXX_SYMBOL_EXISTS_MODULE_DIR
  ${CMAKE_CURRENT_LIST_FILE} PATH)

macro(_DO_SET_SUBSTITUTION_VARIABLES SYMBOL FILES)
  set(SYMBOL_NAME)
  set(SYMBOL_USE)
  set(INCLUDES)
  set(ARG_DECLARATIONS)

  foreach(FILE ${FILES})
    set(INCLUDES "${INCLUDES}\n#include <${FILE}>")
  endforeach()

  # Perform additional processing if SYMBOL is a C++ function call operator
  # (ends with "operator()") or a function overload with parentheses
  # enclosing an (optional) list of argument types.
  if(NOT ${SYMBOL} MATCHES "^.*operator\\(\\)$"
     AND ${SYMBOL} MATCHES "^(.+)\\((.*)\\)$")
    set(SYMBOL_NAME ${CMAKE_MATCH_1})
    set(ARG_LIST)

    string(STRIP ${CMAKE_MATCH_2} CMAKE_MATCH_2)

    # Parse list of function argument types if one is provided.
    if(NOT CMAKE_MATCH_2 STREQUAL "")
      string(LENGTH ${CMAKE_MATCH_2} n) # length of argument type list
      set(i 0) # current index in argument type list string
      set(level 0) # nesting level of "<...>" template argument lists
      set(begin 0) # index of the beginning of the current argument type
      set(count 0) # number of argument types parsed so far

      while(i LESS n)
        string(SUBSTRING ${CMAKE_MATCH_2} ${i} 1 c)
        if(c STREQUAL "<")
          math(EXPR level "${level} + 1")
        elseif(c STREQUAL ">")
          math(EXPR level "${level} - 1")
        elseif(c STREQUAL "," AND level EQUAL 0)
          math(EXPR length "${i} - ${begin}")
          string(SUBSTRING ${CMAKE_MATCH_2} ${begin} ${length} SYMBOL_ARG_TYPE_${count})
          string(STRIP ${SYMBOL_ARG_TYPE_${count}} SYMBOL_ARG_TYPE_${count})
          math(EXPR begin "${i} + 1")
          math(EXPR count "${count} + 1")
        endif()
        if(level LESS 0)
          message(FATAL_ERROR "Invalid symbol name given to CHECK_CXX_SYMBOL_EXISTS(): \"${SYMBOL}\"")
        endif()
        math(EXPR i "${i} + 1")
      endwhile()
      string(SUBSTRING ${CMAKE_MATCH_2} ${begin} -1 SYMBOL_ARG_TYPE_${count})
      string(STRIP ${SYMBOL_ARG_TYPE_${count}} SYMBOL_ARG_TYPE_${count})

      foreach(i RANGE ${count})
        if(SYMBOL_ARG_TYPE_${i} STREQUAL "")
          message(FATAL_ERROR "Invalid symbol name given to CHECK_CXX_SYMBOL_EXISTS(): \"${SYMBOL}\"")
        endif()
        set(ARG_DECLARATIONS "${ARG_DECLARATIONS}${SYMBOL_ARG_TYPE_${i}} arg${i};")
        set(ARG_LIST ${ARG_LIST}arg${i})
        if(i LESS count)
          set(ARG_DECLARATIONS "${ARG_DECLARATIONS}\n  ")
          set(ARG_LIST "${ARG_LIST}, ")
        endif()
      endforeach()
    endif()

    set(SYMBOL_USE "${SYMBOL_NAME}(${ARG_LIST})")
  else()
    set(SYMBOL_NAME ${SYMBOL})
    set(SYMBOL_USE ${SYMBOL})
  endif()
endmacro()

macro(CHECK_CXX_SYMBOL_EXISTS SYMBOL FILES VARIABLE)
  if(NOT DEFINED "${VARIABLE}" OR "x${${VARIABLE}}" STREQUAL "x${VARIABLE}")
    set(_CHECK_CXX_SYMBOL_EXISTS_ADD_INCLUDE_DIRECTORIES)
    set(_CHECK_CXX_SYMBOL_EXISTS_ADD_COMPILE_DEFINITIONS)
    set(_CHECK_CXX_SYMBOL_EXISTS_ADD_LINK_LIBRARIES)

    if(CMAKE_REQUIRED_INCLUDES)
      set(_CHECK_CXX_SYMBOL_EXISTS_ADD_INCLUDE_DIRECTORIES
        "-DINCLUDE_DIRECTORIES:STRING=${CMAKE_REQUIRED_INCLUDES}")
    endif()
    if(CMAKE_REQUIRED_DEFINITIONS)
      set(_CHECK_CXX_SYMBOL_EXISTS_ADD_COMPILE_DEFINITIONS
        COMPILE_DEFINITIONS ${CMAKE_REQUIRED_DEFINITIONS})
    endif()
    if(CMAKE_REQUIRED_LIBRARIES)
      set(_CHECK_CXX_SYMBOL_EXISTS_ADD_LINK_LIBRARIES
        LINK_LIBRARIES ${CMAKE_REQUIRED_LIBRARIES})
    endif()

    _do_set_substitution_variables(${SYMBOL} ${FILES})

    configure_file(${_CHECK_CXX_SYMBOL_EXISTS_MODULE_DIR}/CheckSymbolExists.cxx.in
      ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeTmp/CheckSymbolExists.cxx
      @ONLY)
    file(READ
      ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeTmp/CheckSymbolExists.cxx
      _CHECK_CXX_SYMBOL_EXISTS_SOURCE)

    if(NOT CMAKE_REQUIRED_QUIET)
      message(STATUS "Looking for ${SYMBOL}")
    endif()

    set(CMAKE_CXX_FLAGS_SAVE ${CMAKE_CXX_FLAGS})
    set(CMAKE_CXX_FLAGS ${CMAKE_REQUIRED_FLAGS})

    try_compile(${VARIABLE}
      ${CMAKE_BINARY_DIR}
      ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeTmp/CheckSymbolExists.cxx
      CMAKE_FLAGS ${_CHECK_CXX_SYMBOL_EXISTS_ADD_INCLUDE_DIRECTORIES}
      ${_CHECK_CXX_SYMBOL_EXISTS_ADD_COMPILE_DEFINITIONS}
      ${_CHECK_CXX_SYMBOL_EXISTS_ADD_LINK_LIBRARIES}
      OUTPUT_VARIABLE OUTPUT)

    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS_SAVE})

    if(${VARIABLE})
      if(NOT CMAKE_REQUIRED_QUIET)
        message(STATUS "Looking for ${SYMBOL} - found")
      endif()
      set(${VARIABLE} 1 CACHE INTERNAL "Have symbol ${SYMBOL}")
      file(APPEND ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeOutput.log
        "Determining if the ${SYMBOL} "
        "exists passed with the following output:\n"
        "${OUTPUT}\nFile ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeTmp/CheckSymbolExists.cxx:\n"
        "${_CHECK_CXX_SYMBOL_EXISTS_SOURCE}\n")
    else()
      if(NOT CMAKE_REQUIRED_QUIET)
        message(STATUS "Looking for ${SYMBOL} - not found")
      endif()
      set(${VARIABLE} "" CACHE INTERNAL "Have symbol ${SYMBOL}")
      file(APPEND ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeError.log
        "Determining if the ${SYMBOL} "
        "exists failed with the following output:\n"
        "${OUTPUT}\nFile ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeTmp/CheckSymbolExists.cxx:\n"
        "${_CHECK_CXX_SYMBOL_EXISTS_SOURCE}\n")
    endif()
  endif()
endmacro()
