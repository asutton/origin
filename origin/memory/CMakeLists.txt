# Copyright (c) 2009-2015 Andrew Sutton
# All rights reserved

include(GenerateExportHeader)

# Set variables.

# Add options.

# Run platform checks.

# Set compiler and linker flags.
add_compiler_export_flags()

# Add a library.
add_library(origin-memory STATIC
  memory.cpp
  allocator.cpp)

target_compile_options(origin-memory PUBLIC -std=c++1z)
target_include_directories(origin-memory
  PUBLIC "$<BUILD_INTERFACE:${Origin_SOURCE_DIR};${Origin_BINARY_DIR}>")
target_link_libraries(origin-memory PUBLIC origin-core)

add_dependencies(check origin-memory)

# Generate the configuration header.
configure_file(config.hpp.in config.hpp)

# Generate the export header.
generate_export_header(origin-memory EXPORT_FILE_NAME export.hpp)

# Add subdirectories.

# Add install targets.
install(
  TARGETS origin-memory
  EXPORT OriginTargets
  RUNTIME DESTINATION "${INSTALL_BIN_DIR}"
  LIBRARY DESTINATION "${INSTALL_LIB_DIR}"
  ARCHIVE DESTINATION "${INSTALL_LIB_DIR}"
  INCLUDES DESTINATION "${INSTALL_INCLUDE_DIR}"
)
