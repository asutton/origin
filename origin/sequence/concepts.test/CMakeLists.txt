# Copyright (c) 2008-2014 Andrew Sutton
#
# This file is distributed under the MIT License. See the accompanying file
# LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
# and conditions.

add_run_test(iter_readable readable.cpp)
add_run_test(iter_writable writable.cpp)
add_run_test(iter_permutable permutable.cpp)
add_run_test(iter_mutable mutable.cpp)

add_run_test(iter_advanceable advanceable.cpp)
add_run_test(iter_incrementable incrementable.cpp)

add_run_test(iter_input_iterator input_iterator.cpp)
add_run_test(iter_output_iterator output_iterator.cpp)
add_run_test(iter_forward_iterator forward_iterator.cpp)
add_run_test(iter_bidirectional_iterator bidirectional_iterator.cpp)
add_run_test(iter_random_access_iterator random_access_iterator.cpp)

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
