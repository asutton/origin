# This file is distributed under the MIT License. See the accompanying file
# LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
# and conditions.

add_library(origin-core
  traits.cpp
  concepts.cpp
  function.cpp
  type.cpp
)

# FIXME: The tests in this library need to link against
# the origin-core library.

add_subdirectory(concepts.test)
add_subdirectory(function.test)

