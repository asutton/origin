# Copyright (c) 2008-2013 Andrew Sutton
#
# This file is distributed under the MIT License. See the accompanying file
# LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
# and conditions.

cmake_minimum_required(VERSION 2.8)

# Set the project, required language, and default flags.
project(origin CXX)
set(CMAKE_CXX_FLAGS -std=c++1y)

enable_testing()

macro(add_run_test target file)
  add_executable(${target} ${file})
  add_test(test_${target} ${target})
endmacro()

# Always have the top-level directory on path.
include_directories(.)

add_subdirectory(origin)
add_subdirectory(origin.math)
