# Copyright (c) 2008-2013 Andrew Sutton
#
# This file is distributed under the MIT License. See the accompanying file
# LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
# and conditions.

add_run_test(range_range range.cpp)
add_run_test(range_input_range input_range.cpp)
add_run_test(range_output_range output_range.cpp)
add_run_test(range_forward_range forward_range.cpp)
add_run_test(range_bidirectional_range bidirectional_range.cpp)
add_run_test(range_random_access_range random_access_range.cpp)

add_run_test(range_iterator_type iterator_type.cpp)
add_run_test(range_size_type size_type.cpp)
