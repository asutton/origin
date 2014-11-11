// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

namespace origin {

// ---------------------------------------------------------------------------//
// Abstract allocator

inline
allocator::~allocator() { }

inline void*
allocator::allocate(int n) { return ::operator new(n); }

inline void
allocator::deallocate(void* p) { ::operator delete(p); }

} // namespace
