// Copyright (c) 2008-2013 Andrew Sutton
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#ifndef TEST_ITERATOR_HPP
#define TEST_ITERATOR_HPP

// A move-only type
struct input_iter
{
  input_iter& operator++() { return *this; }
};

bool operator==(input_iter, input_iter) { return true; }
bool operator!=(input_iter, input_iter) { return true; }


#endif
