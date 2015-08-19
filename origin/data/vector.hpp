// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#ifndef ORIGIN_CORE_DATA_HPP
#define ORIGIN_CORE_DATA_HPP

#include <origin/concepts.hpp>
#include <origin/memory.hpp>


namespace origin 
{

template<Object_type T, Allocator A = allocator>
struct vector : private std::vector<T, std_allocator<T, A>>
{

};


} // namespace origin

#endif
