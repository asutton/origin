# Copyright (c) 2009-2015 Andrew Sutton
# All rights reserved

cmake_minimum_required(VERSION 3.0)

# Set CMake module path.
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(CheckCXXCompilerFlag)
include(CheckCXXConcepts)
include(CMakePackageConfigHelpers)
include(GNUInstallDirs)
include(OriginTesting)
include(OriginUtilities)

# Add a project.
project(Origin VERSION 0.1 LANGUAGES CXX)

# Set variables.
set(ORIGIN_PACKAGE_NAME ${PROJECT_NAME})
set(ORIGIN_PACKAGE_TARNAME ${ORIGIN_PACKAGE_NAME})
set(ORIGIN_PACKAGE_VERSION ${PROJECT_VERSION})
set(ORIGIN_PACKAGE_STRING "${ORIGIN_PACKAGE_NAME} ${ORIGIN_PACKAGE_VERSION}")
set(ORIGIN_PACKAGE_BUGREPORT "https://github.com/asutton/origin/issues")
set(ORIGIN_PACKAGE_URL "https://github.com/asutton/origin")
set(ORIGIN_VERSION ${PROJECT_VERSION})

foreach(component MAJOR MINOR PATCH TWEAK)
  if(PROJECT_VERSION_${component} STREQUAL "")
    set(PROJECT_VERSION_${component} 0)
  endif()
endforeach()

set(ORIGIN_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(ORIGIN_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(ORIGIN_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(ORIGIN_VERSION_TWEAK ${PROJECT_VERSION_TWEAK})

set(INSTALL_BIN_DIR ${CMAKE_INSTALL_BINDIR})
set(INSTALL_LIB_DIR ${CMAKE_INSTALL_LIBDIR})
set(INSTALL_INCLUDE_DIR ${CMAKE_INSTALL_INCLUDEDIR})
set(INSTALL_DATA_DIR ${CMAKE_INSTALL_DATADIR})

# Add .ipp and .IPP to list of ignored file extensions for C++.
list(APPEND CMAKE_CXX_IGNORE_EXTENSIONS "ipp" "IPP")
list(REMOVE_DUPLICATES CMAKE_CXX_IGNORE_EXTENSIONS)

# Set output location of built targets.
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

# Add options.
option(BUILD_SHARED_LIBS "Build shared libraries." ON)

# Enable testing.
enable_testing()

# Run platform checks.
# Make sure that we have C++1z...
check_cxx_compiler_flag(-std=c++1z CXX_COMPILER_HAS_STDCXX1Z_FLAG)
if(NOT CXX_COMPILER_HAS_STDCXX1Z_FLAG)
  message(FATAL_ERROR "${PROJECT_NAME} requires a C++ compiler that supports -std=c++1z.")
endif()

# ... and that concepts are included in C++1z.
# TODO: What happens when there are different versions of concepts?
set(CMAKE_REQUIRED_FLAGS -fconcepts)
check_cxx_concepts(CXX_COMPILER_HAS_CONCEPTS)
if(NOT CXX_COMPILER_HAS_CONCEPTS)
  message(FATAL_ERROR "${PROJECT_NAME} requires a C++ compiler that supports concepts.")
endif()

# Set compiler and linker flags.

# Generate the compilation test driver script.
generate_compile_test_driver(CompileTestDriver.cmake)

# Generate CTest custom script.
configure_file(CTestCustom.cmake.in CTestCustom.cmake @ONLY)

# Add 'check' target.
if(NOT TARGET check)
  add_custom_target(
    check
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target test
  )
endif()

# Add 'uninstall' target.
if(NOT TARGET uninstall)
  configure_file(
    ${PROJECT_SOURCE_DIR}/cmake_uninstall.cmake.in
    ${CMAKE_BINARY_DIR}/cmake_uninstall.cmake
    @ONLY
  )
  add_custom_target(
    uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_BINARY_DIR}/cmake_uninstall.cmake
  )
endif()

# Add subdirectories.
add_subdirectory(origin)
add_subdirectory(origin.math)
add_subdirectory(examples/hello)
add_subdirectory(cmake)

# Export targets from the build tree.
export(EXPORT OriginTargets)

# Add install targets.
install(
  DIRECTORY ${PROJECT_SOURCE_DIR}/origin ${PROJECT_BINARY_DIR}/origin
  DESTINATION ${INSTALL_INCLUDE_DIR}
  FILES_MATCHING
  PATTERN "*.hpp"
  PATTERN "*.ipp"
  PATTERN "CMakeFiles" EXCLUDE
  PATTERN "*.test" EXCLUDE
)
