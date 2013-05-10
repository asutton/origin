# Copyright (c) 2008-2013 Andrew Sutton
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