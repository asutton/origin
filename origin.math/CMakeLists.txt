# Copyright (c) 2009-2015 Andrew Sutton
# All rights reserved

include(GenerateExportHeader)

# Set variables.

# Add options.

# Run platform checks.

# Set compiler and linker flags.
add_compiler_export_flags()

# Add a library.
add_library(origin-math STATIC
  numeric.cpp
  stats.cpp)

target_compile_options(origin-math PUBLIC -std=c++1z -fconcepts)
target_include_directories(origin-math
  PUBLIC "$<BUILD_INTERFACE:${Origin_SOURCE_DIR};${Origin_BINARY_DIR}>")

add_dependencies(check origin-math)

# Generate the configuration header.
configure_file(config.hpp.in config.hpp)

# Generate the export header.
generate_export_header(origin-math EXPORT_FILE_NAME export.hpp)

# Add subdirectories.

# Add install targets.
# install(
#   TARGETS origin-math
#   EXPORT OriginTargets
#   RUNTIME DESTINATION ${INSTALL_BIN_DIR}
#   LIBRARY DESTINATION ${INSTALL_LIB_DIR}
#   ARCHIVE DESTINATION ${INSTALL_LIB_DIR}
#   INCLUDES DESTINATION ${INSTALL_INCLUDE_DIR}
# )
