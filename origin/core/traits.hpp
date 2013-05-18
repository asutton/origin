// Copyright (c) 2008-2013 Andrew Sutton
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#ifndef ORIGIN_CORE_TRAITS_HPP
#define ORIGIN_CORE_TRAITS_HPP

#include <type_traits>

namespace origin {

// Primary type categories

// Void_type
template<typename T>
  concept bool Void_type() { return std::is_void<T>::value; }

// Integral_type
template<typename T>
  concept bool Integral_type() { return std::is_integral<T>::value; }

// Floating_point_type
template<typename T>
  concept bool Floating_point_type() { return std::is_floating_point<T>::value; }

// Array_type
template<typename T>
  concept bool Array_type() { return std::is_array<T>::value; }

// Pointer_type
template<typename T>
  concept bool Pointer_type() { return std::is_pointer<T>::value; }

// Lvalue_reference_type
template<typename T>
  concept bool Lvalue_reference_type() { return std::is_lvalue_reference<T>::value; }

// Rvalue_reference_type
template<typename T>
  concept bool Rvalue_reference_type() { return std::is_rvalue_reference<T>::value; }

// Member_object_pointer_type
template<typename T>
  concept bool Member_object_pointer_type() 
  { 
    return std::is_member_object_pointer<T>::value; 
  }

// Member_function_pointer_type
template<typename T>
  concept bool Member_function_pointer_type() 
  { 
    return std::is_member_function_pointer<T>::value; 
  }

// Enum_type
template<typename T>
  concept bool Enum_type() { return __is_enum(T); }

// Union_type
template<typename T>
  concept bool Union_type() { return __is_union(T); }

// Class_type
template<typename T>
  concept bool Class_type() { return __is_class(T); }

// Function_type
template<typename T>
  concept bool Function_type() { return std::is_function<T>::value; }


// Composite type categories
// TODO: Rewrite all composite types in terms of primary
// categories so that we get proper refinements.

// Reference_type
template<typename T>
  concept bool Reference_type()
  {
    return Lvalue_reference_type<T>() || Rvalue_reference_type<T>();
  }

// Arithmetic_type
template<typename T>
  concept bool Arithmetic_type()
  {
    return Integral_type<T>() || Floating_point_type<T>();
  }

// Fundamental_type
template<typename T>
  concept bool Fundamental_type() { return std::is_fundamental<T>::value; }

// Object_type
template<typename T>
  concept bool Object_type() { return std::is_object<T>::value; }

// Scalar_type
template<typename T>
  concept bool Scalar_type() { return std::is_scalar<T>::value; }

// Compound_type
template<typename T>
  concept bool Compound_type() { return std::is_compound<T>::value; }

// Member_pointer_type
template<typename T>
  concept bool Member_pointer_type() { return std::is_member_pointer<T>::value; }


// Type properties
// TODO: Finish implementing type properties

// Const_type
template<typename T>
  concept bool Const_type() { return std::is_const<T>::value; }

// Volatile_type
template<typename T>
  concept bool Volatile_type() { return std::is_volatile<T>::value; }

// Qualified_type
template<typename T>
  concept bool Qualified_type() { return Const_type<T>() || Volatile_type<T>(); }


// Type transformations

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

// Main_type
template<typename T>
  using Main_type = Remove_cv<Remove_reference<T>>;

} // namespace origin

#endif
