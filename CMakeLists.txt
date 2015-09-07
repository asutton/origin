# Copyright (c) 2009-2015 Andrew Sutton
# All rights reserved


cmake_minimum_required(VERSION 2.8)


# Set the project, required language, and default flags.
project(origin CXX)
set(CMAKE_CXX_FLAGS -std=c++1z)


enable_testing()


macro(add_run_test target file)
  add_executable(${target} ${file})
  add_test(test_${target} ${target})
endmacro()


# Always have the top-level directory on path.
include_directories(.)

add_subdirectory(origin)
add_subdirectory(origin.math)

add_subdirectory(examples/hello)
