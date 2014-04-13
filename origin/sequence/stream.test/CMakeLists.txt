# Copyright (c) 2008-2013 Andrew Sutton
#
# This file is distributed under the MIT License. See the accompanying file
# LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
# and conditions.

add_run_test(stream_concepts concepts.cpp)
add_run_test(stream_typed_istream typed_istream.cpp)
add_run_test(stream_typed_ostream typed_ostream.cpp)

add_run_test(stream_istream_range istream_range.cpp)
add_run_test(stream_istream_for istream_for.cpp)

add_run_test(stream_ostream_range ostream_range.cpp)

add_run_test(stream_experiment experiment.cpp)
