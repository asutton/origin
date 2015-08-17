// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#ifndef TEST_ITERATOR_HPP
#define TEST_ITERATOR_HPP

// A simple input iterator model.
struct input_iter 
{
  input_iter& operator++() { return *this; }
};

bool operator==(input_iter, input_iter) { return true; }
bool operator!=(input_iter, input_iter) { return true; }


#endif
