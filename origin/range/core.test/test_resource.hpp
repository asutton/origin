// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#ifndef TEST_RESOURCE_HPP
#define TEST_RESOURCE_HPP

// A move-only type.
struct res 
{
  res(res&&) = default;
  res& operator=(res&&) = default;
  
  res(const res&) = delete;
  res& operator=(const res&) = delete;
};

#endif
