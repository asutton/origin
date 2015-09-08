# Copyright (c) 2009-2015 Andrew Sutton
# All rights reserved

include(CheckCXXSymbolExists)
include(GenerateExportHeader)

# Set variables.

# Add options.

# Run platform checks.
check_cxx_symbol_exists("std::to_string(std::size_t)" "string"
  ORIGIN_HAVE_STD_TO_STRING)

# Set compiler and linker flags.
add_compiler_export_flags()

# Add a library.
add_library(origin-core STATIC
  traits.cpp
  concepts.cpp
  function.cpp
  finally.cpp
  type.cpp)

target_compile_options(origin-core PUBLIC -std=c++1z)
target_include_directories(origin-core
  PUBLIC "$<BUILD_INTERFACE:${Origin_SOURCE_DIR};${Origin_BINARY_DIR}>")
add_dependencies(check origin-core)

# Generate the configuration header.
configure_file(config.hpp.in config.hpp)

# Generate the export header.
generate_export_header(origin-core EXPORT_FILE_NAME export.hpp)

# Add subdirectories.
add_subdirectory(concepts.test)
add_subdirectory(function.test)
add_subdirectory(finally.test)

# Add install targets.
install(
  TARGETS origin-core
  EXPORT OriginTargets
  RUNTIME DESTINATION "${INSTALL_BIN_DIR}"
  LIBRARY DESTINATION "${INSTALL_LIB_DIR}"
  ARCHIVE DESTINATION "${INSTALL_LIB_DIR}"
  INCLUDES DESTINATION "${INSTALL_INCLUDE_DIR}"
)
