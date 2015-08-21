// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#ifndef ORIGIN_CORE_SEMANTICS_HPP
#define ORIGIN_CORE_SEMANTICS_HPP

#include <cassert>

// Terminate the program if the precondition `e` evaluates
// to false.
#define expects(e) assert(e)


// Terminates the program if the postcondition `e` evalautes
// to false.
#define ensures(e) assert(e)

#endif
