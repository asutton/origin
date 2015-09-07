# Copyright (c) 2009-2015 Andrew Sutton
# All rights reserved

add_library(origin-core
  traits.cpp
  concepts.cpp
  function.cpp
  finally.cpp
  type.cpp)

# FIXME: The tests in this library need to link against
# the origin-core library.

add_subdirectory(concepts.test)
add_subdirectory(function.test)
add_subdirectory(finally.test)

