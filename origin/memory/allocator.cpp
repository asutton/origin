// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#include "allocator.hpp"

namespace origin {

namespace {

// The global default allocator.
new_allocator alloc_;

} // namespace

// Returns the default allocator.
allocator& 
default_allocator() { return alloc_; }

} // namespace origin
