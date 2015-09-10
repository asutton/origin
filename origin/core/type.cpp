// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#include "type.hpp"

#include <cstdlib>

#if defined(__GNUC__)
#  include <cxxabi.h>
#endif


namespace origin
{

// Return the string represntation of a type info object.
#if defined(__GNUC__)

std::string
typestr(std::type_info const& info)
{
  std::size_t n = 0;
  char* buf = abi::__cxa_demangle(info.name(), nullptr, &n, 0);
  std::string result(buf, n);
  std::free(buf);
  return result;
}

#else
#  error No compiler support for rendering type names
#endif

} // namespace origin
