// Copyright (c) 2008-2013 Andrew Sutton
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#include <origin/core/concepts.hpp>

static_assert(origin::Convertible<int, int>(), "");
static_assert(origin::Convertible<int, const int>(), "");
static_assert(origin::Convertible<int, volatile int>(), "");
static_assert(origin::Convertible<int, const volatile int>(), "");
static_assert(origin::Convertible<const int, int>(), "");
static_assert(origin::Convertible<volatile int, int>(), "");
static_assert(origin::Convertible<const volatile int, int>(), "");

static_assert(not origin::Convertible<int, int&>(), "");
static_assert(not origin::Convertible<const int, int&>(), "");
static_assert(not origin::Convertible<volatile int, int&>(), "");
static_assert(not origin::Convertible<const volatile int, int&>(), "");

static_assert(origin::Convertible<int, const int&>(), "");
static_assert(origin::Convertible<const int, const int&>(), "");
static_assert(not origin::Convertible<volatile int, const int&>(), "");
static_assert(not origin::Convertible<const volatile int, const int&>(), "");

static_assert(origin::Convertible<int, int&&>(), "");



static_assert(origin::Convertible<int&, int>(), "");
static_assert(origin::Convertible<const int&, int>(), "");



// TODO: Write more tests.

int main() { return 0; }
