# Copyright (c) 2009-2015 Andrew Sutton
# All rights reserved

# Add subdirectories.
add_subdirectory(core)
add_subdirectory(memory)
add_subdirectory(iterator)
add_subdirectory(range)
add_subdirectory(algorithm)
add_subdirectory(data)
# add_subdirectory(numeric)

# Add a library.
add_library(origin origin.cpp)
target_link_libraries(origin PUBLIC
  origin-core
  origin-memory
  origin-iterator
  origin-range
  origin-algorithm
  origin-data)
