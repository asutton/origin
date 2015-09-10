# Copyright (c) 2009-2015 Andrew Sutton
# All rights reserved

include(GenerateExportHeader)

# Set variables.

# Add options.

# Run platform checks.

# Set compiler and linker flags.
add_compiler_export_flags()

# Add a library.
add_library(origin-algorithm STATIC
  concepts.cpp
  copy.cpp
  count.cpp
  equal.cpp
  find.cpp
  foreach.cpp
  quantifier.cpp
  uninitialized.cpp)

target_compile_options(origin-algorithm PUBLIC -std=c++1z)
target_include_directories(origin-algorithm
  PUBLIC "$<BUILD_INTERFACE:${Origin_SOURCE_DIR};${Origin_BINARY_DIR}>")
target_link_libraries(origin-algorithm
  PUBLIC origin-core origin-iterator origin-memory origin-range)

add_dependencies(check origin-algorithm)

# Generate the configuration header.
configure_file(config.hpp.in config.hpp)

# Generate the export header.
generate_export_header(origin-algorithm EXPORT_FILE_NAME export.hpp)

# Add subdirectories.
add_subdirectory(algorithm.test)

# Add install targets.
install(
  TARGETS origin-algorithm
  EXPORT OriginTargets
  RUNTIME DESTINATION "${INSTALL_BIN_DIR}"
  LIBRARY DESTINATION "${INSTALL_LIB_DIR}"
  ARCHIVE DESTINATION "${INSTALL_LIB_DIR}"
  INCLUDES DESTINATION "${INSTALL_INCLUDE_DIR}"
)
