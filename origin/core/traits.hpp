// Copyright (c) 2008-2013 Andrew Sutton
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#ifndef ORIGIN_CORE_TRAITS_HPP
#define ORIGIN_CORE_TRAITS_HPP

#include <type_traits>

namespace origin {

// Remove_const
template<typename T>
  using Remove_const = typename std::remove_const<T>::type;

// Remove_volatile
template<typename T>
  using Remove_volatile = typename std::remove_volatile<T>::type;

// Remove_cv
template<typename T>
  using Remove_cv = typename std::remove_cv<T>::type;

// Add_const
template<typename T>
  using Add_const = typename std::add_const<T>::type;

// Add_volatile
template<typename T>
  using Add_volatile = typename std::add_volatile<T>::type;

// Add_cv
template<typename T>
  using Add_cv = typename std::add_cv<T>::type;

// Remove_reference
template<typename T>
  using Remove_reference = typename std::remove_reference<T>::type;

// Add_lvalue_reference
template<typename T>
  using Add_lvalue_reference = typename std::add_lvalue_reference<T>::type;

// Add_rvalue_reference
template<typename T>
  using Add_rvalue_reference = typename std::add_rvalue_reference<T>::type;

// Make_signed
template<typename T>
  using Make_signed = typename std::make_signed<T>::type;

// Make_unsigned
template<typename T>
  using Make_unsigned = typename std::make_unsigned<T>::type;

// Remove_extent
template<typename T>
  using Remove_extent = typename std::remove_extent<T>::type;

// Remove_all_extents
template<typename T>
  using Remove_all_extents = typename std::remove_all_extents<T>::type;

// Remove_pointer
template<typename T>
  using Remove_pointer = typename std::remove_pointer<T>::type;

// Add_pointer
template<typename T>
  using Add_pointer = typename std::add_pointer<T>::type;

} // namespace origin

#endif
