# Copyright (c) 2009-2015 Andrew Sutton
# All rights reserved

link_libraries(origin-iterator)

# Read/write categories
add_run_test(iter_readable                readable.cpp)
add_run_test(iter_writable                writable.cpp)
add_run_test(iter_permutable              permutable.cpp)
add_run_test(iter_mutable                 mutable.cpp)

# Basic traveral categories
add_run_test(iter_advanceable             advanceable.cpp)
add_run_test(iter_incrementable           incrementable.cpp)

# Iterator categories
add_run_test(iter_input_iterator          input_iterator.cpp)
add_run_test(iter_output_iterator         output_iterator.cpp)
add_run_test(iter_forward_iterator        forward_iterator.cpp)
add_run_test(iter_bidirectional_iterator  bidirectional_iterator.cpp)
add_run_test(iter_random_access_iterator  random_access_iterator.cpp)

# Associated type tests
add_run_test(iter_value_type              value_type.cpp)
