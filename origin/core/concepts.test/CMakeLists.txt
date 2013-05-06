# Copyright (c) 2008-2013 Andrew Sutton
#
# This file is distributed under the MIT License. See the accompanying file
# LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
# and conditions.

add_run_test(core_same same.cpp)
add_run_test(core_derived derived.cpp)
add_run_test(core_convertible convertible.cpp)

add_run_test(core_equality_comparable equality_comparable.cpp)
add_run_test(core_weakly_ordered weakly_ordered.cpp)
add_run_test(core_totally_ordered totally_ordered.cpp)

