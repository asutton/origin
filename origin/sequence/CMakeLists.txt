# Copyright (c) 2009-2015 Andrew Sutton
# All rights reserved

add_library(origin-sequence
  uninitialized.cpp)

add_subdirectory(concepts.test)
add_subdirectory(range.test)
add_subdirectory(algorithm.test)

# TODO: Add tests for uninitialized copy.

# add_subdirectory(stream.test)
