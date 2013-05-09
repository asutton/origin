// Copyright (c) 2008-2013 Andrew Sutton
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#ifndef TEST_RESOURCE_HPP
#define TEST_RESOURCE_HPP

// A move-only type
struct res
{
  res(res&&) = default;
  res& operator=(res&&) = default;
  res(const res&) = delete;
  res& operator=(const res&) = delete;
};

#endif
