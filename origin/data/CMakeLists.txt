# Copyright (c) 2009-2015 Andrew Sutton
# All rights reserved

include(GenerateExportHeader)

# Set variables.

# Add options.
# option(ORIGIN_USE_SSO "Enable the short/small string optimization." ON)

# Run platform checks.

# Set compiler and linker flags.
add_compiler_export_flags()

# Add the library.
add_library(origin-data STATIC
  vector.cpp)

target_compile_options(origin-data PUBLIC -std=c++1z -fconcepts)
target_include_directories(origin-data
  PUBLIC "$<BUILD_INTERFACE:${Origin_SOURCE_DIR};${Origin_BINARY_DIR}>")
target_link_libraries(origin-data
  PUBLIC origin-iterator origin-memory origin-range)

add_dependencies(check origin-data)

# Generate the configuration header.
configure_file(config.hpp.in config.hpp)

# Generate the export header.
generate_export_header(origin-data EXPORT_FILE_NAME export.hpp)

# Add subdirectories.
# TODO: Add tests.

# Add install targets.
install(
  TARGETS origin-data
  EXPORT OriginTargets
  RUNTIME DESTINATION ${INSTALL_BIN_DIR}
  LIBRARY DESTINATION ${INSTALL_LIB_DIR}
  ARCHIVE DESTINATION ${INSTALL_LIB_DIR}
  INCLUDES DESTINATION ${INSTALL_INCLUDE_DIR}
)
