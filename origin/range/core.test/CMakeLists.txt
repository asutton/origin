# Copyright (c) 2009-2015 Andrew Sutton
# All rights reserved

link_libraries(origin-range)

add_run_test(range_iterator_type iterator_type.cpp)
add_run_test(range_sentinel_type sentinel_type.cpp)

add_run_test(range_range range.cpp)
add_run_test(range_input_range input_range.cpp)
add_run_test(range_output_range output_range.cpp)
add_run_test(range_forward_range forward_range.cpp)
add_run_test(range_bidirectional_range bidirectional_range.cpp)
add_run_test(range_random_access_range random_access_range.cpp)

add_run_test(range_size_type size_type.cpp)
add_run_test(range_value_type value_type.cpp)
