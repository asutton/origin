# Copyright (c) 2009-2015 Andrew Sutton
# All rights reserved

link_libraries(origin-algorithm)

add_run_test(range_algo_for_each for_each.cpp)

add_run_test(range_algo_all_of all_of.cpp)
add_run_test(range_algo_any_of any_of.cpp)
add_run_test(range_algo_none_of none_of.cpp)
add_run_test(range_algo_count_if count_if.cpp)

# add_run_test(range_algo_find find.cpp)
# add_run_test(range_algo_find_if find_if.cpp)
# add_run_test(range_algo_find_if_not find_if_not.cpp)

# add_run_test(range_algo_count count.cpp)
# add_run_test(range_algo_adjacent_find adjacent_find.cpp)
# add_run_test(range_algo_mismatch mismatch.cpp)
# add_run_test(range_algo_equal equal.cpp)
# add_run_test(range_algo_find_first_of find_first_of.cpp)
# add_run_test(range_algo_find_end find_end.cpp)

add_run_test(seq_algo_copy copy.cpp)
