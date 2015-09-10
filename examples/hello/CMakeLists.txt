# Copyright (c) 2009-2015 Andrew Sutton
# All rights reserved

# Add an executable.
add_executable(hello EXCLUDE_FROM_ALL hello.cpp)
target_link_libraries(hello origin-core)
