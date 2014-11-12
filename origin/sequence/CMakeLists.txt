# Copyright (c) 2008-2014 Andrew Sutton
#
# This file is distributed under the MIT License. See the accompanying file
# LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
# and conditions.

# FIXME: This is simply not a complete algorithm.
add_library(origin-sequence
  uninitialized.cpp
)

add_subdirectory(concepts.test)
add_subdirectory(range.test)
add_subdirectory(algorithm.test)

# TODO: Add tests for uninitialized copy.

# add_subdirectory(stream.test)
