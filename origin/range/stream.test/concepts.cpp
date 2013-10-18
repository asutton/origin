// Copyright (c) 2008-2013 Andrew Sutton
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#include <iostream>
#include <sstream>
#include <fstream>

#include <origin/core/type.hpp>
#include <origin/range/stream.hpp>

using Istream = std::istream;
using Isstream = std::istringstream;
using Ifstream = std::ifstream;

using Ostream = std::ostream;
using Osstream = std::ostringstream;
using Ofstream = std::ofstream;

static_assert(origin::Input_stream<Istream>(), "");
static_assert(origin::Input_stream<Isstream>(), "");
static_assert(origin::Input_stream<Ifstream>(), "");

static_assert(origin::Output_stream<Ostream>(), "");
static_assert(origin::Output_stream<Osstream>(), "");
static_assert(origin::Output_stream<Ofstream>(), "");

// Formatted input streams
// We could test for the entire suite of overloads expected by
// the basic_istream class.
static_assert(origin::Formatted_input_stream<Istream, char>(), "");
static_assert(origin::Formatted_input_stream<Istream, int>(), "");
static_assert(origin::Formatted_input_stream<Istream, std::string>(), "");

static_assert(origin::Formatted_input_stream<Isstream, char>(), "");
static_assert(origin::Formatted_input_stream<Isstream, int>(), "");
static_assert(origin::Formatted_input_stream<Isstream, std::string>(), "");

static_assert(origin::Formatted_input_stream<Ifstream, char>(), "");
static_assert(origin::Formatted_input_stream<Ifstream, int>(), "");
static_assert(origin::Formatted_input_stream<Ifstream, std::string>(), "");

// Formatted output streams
static_assert(origin::Formatted_output_stream<Ostream, char>(), "");
static_assert(origin::Formatted_output_stream<Ostream, int>(), "");
static_assert(origin::Formatted_output_stream<Ostream, const char*>(), "");
static_assert(origin::Formatted_output_stream<Ostream, std::string>(), "");

// TODO: Test adaptors
using Int_istream = origin::typed_istream<Istream, int>;
using Int_isstream = origin::typed_istream<Isstream, int>;
using Int_ifstream = origin::typed_istream<Ifstream, int>;

static_assert(origin::Input_stream<Int_istream>(), "");
static_assert(origin::Input_stream<Int_isstream>(), "");
static_assert(origin::Input_stream<Int_ifstream>(), "");

using Int_ostream = origin::typed_ostream<Ostream, int>;
using Int_osstream = origin::typed_ostream<Osstream, int>;
using Int_ofstream = origin::typed_ostream<Ofstream, int>;

static_assert(origin::Output_stream<Int_ostream>(), "");
static_assert(origin::Output_stream<Int_osstream>(), "");
static_assert(origin::Output_stream<Int_ofstream>(), "");

int main() { }
