# Copyright (c) 2008-2013 Andrew Sutton
#
# This file is distributed under the MIT License. See the accompanying file
# LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
# and conditions.

include(GenerateExportHeader)

# Set variables.

# Add options.

# Run platform checks.

# Set compiler and linker flags.
add_compiler_export_flags()

# Add a library.
add_library(origin-graph STATIC
  adjacency_list.cpp
  adjacency_vector.cpp)

target_compile_options(origin-graph PUBLIC -std=c++1z)
target_include_directories(origin-graph
  PUBLIC "$<BUILD_INTERFACE:${Origin_SOURCE_DIR};${Origin_BINARY_DIR}>")
target_link_libraries(origin-graph PUBLIC origin-core origin-range)

add_dependencies(check origin-graph)

# Generate the configuration header.
configure_file(config.hpp.in config.hpp)

# Generate the export header.
generate_export_header(origin-graph EXPORT_FILE_NAME export.hpp)

# Add subdirectories.
add_subdirectory(handle.test)
add_subdirectory(adjacency_list.test)

# Add install targets.
# install(
#   TARGETS origin-graph
#   EXPORT OriginTargets
#   RUNTIME DESTINATION "${INSTALL_BIN_DIR}"
#   LIBRARY DESTINATION "${INSTALL_LIB_DIR}"
#   ARCHIVE DESTINATION "${INSTALL_LIB_DIR}"
#   INCLUDES DESTINATION "${INSTALL_INCLUDE_DIR}"
# )
