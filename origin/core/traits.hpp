// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#ifndef ORIGIN_CORE_TRAITS_HPP
#define ORIGIN_CORE_TRAITS_HPP

#include <type_traits>

namespace origin {

// Primary type categories

// Returns true if an only if `T` is possibly cv-qualified `void.`
template<typename T>
  concept bool 
  Void_type() { return std::is_void<T>::value; }

// Returns true if an only if `T` is a possibly cv-qualified integral
// type. The integral types are:
//
// * `bool`
// * `char`, `signed char`, `unsigned char`
// * `wchar_t`, `char16_t`, `char32_t`
// * `short`, `unsigned short`
// * `int`, `unsigned int`
// * `long`, `unsigned long`
// * `long long`, `unsigned long long`
// * any extended integral types
//
// Note that the set of extended integral types is implementation
// defined.
template<typename T>
  concept bool 
  Integral_type() { return std::is_integral<T>::value; }

// Returns true if and only if T is a (possibly cv-qualified) floating 
// point type. The floating point types are:
//
// * `float`
// * `double`
// * `long double`
template<typename T>
  concept bool 
  Floating_point_type() { 
    return std::is_floating_point<T>::value; 
  }

// Is true if and only if T is an array type of known or unknown 
// bounds. Array types include those with the following form:
//
// * `T[]`
// * `T[M]`
//
// where `T` is a type and `N` is an integral constant expression.
template<typename T>
  concept bool 
  Array_type() { 
    return std::is_array<T>::value; 
  }

// Is true if and only if T is an object pointer type. Note that is
// false for member object pointers.
template<typename T>
  concept bool 
  Pointer_type() { 
    return std::is_pointer<T>::value; 
  }

// Is true if and only if T is an lvalue reference type.
template<typename T>
  concept bool 
  Lvalue_reference_type() { 
    return std::is_lvalue_reference<T>::value; 
  }

// Is true if and only if T is an rvalue reference type.
template<typename T>
  concept bool 
  Rvalue_reference_type() { 
    return std::is_rvalue_reference<T>::value; 
  }

// Is true if and only if T is a pointer to a member object.
template<typename T>
  concept bool 
  Member_object_pointer_type() {
    return std::is_member_object_pointer<T>::value; 
  }

// Is true if and only if T is a pointer to a member function.
template<typename T>
  concept bool 
  Member_function_pointer_type() {
    return std::is_member_function_pointer<T>::value; 
  }

// Is true if and only if T is an enumerated type.
template<typename T>
  concept bool 
  Enum_type() { return __is_enum(T); }

// Is true if and only if T is a union type.
template<typename T>
  concept bool 
  Union_type() { return __is_union(T); }

// Is true if and only is a class type.
template<typename T>
  concept bool 
  Class_type() { return __is_class(T); }

// Is true if and only if T is a function type.
template<typename T>
  concept bool 
  Function_type() { return std::is_function<T>::value; }


// Composite type categories

// Is true if and only T is a reference type. A reference type is either 
// an lvalue or rvalue reference type.
template<typename T>
  concept bool 
  Reference_type() {
    return Lvalue_reference_type<T>() || Rvalue_reference_type<T>();
  }

// Is true if and only if T is an arithmetic type. Arithmetic types include
// both integral and floating point types.
template<typename T>
  concept bool 
  Arithmetic_type() {
    return Integral_type<T>() || Floating_point_type<T>();
  }

// Is true if and only if T is a fundamental type. The fundamental types are 
// the built-in types of the programming language and include:
//   * void
//   * nullptr_t
//   * arithmetic types
//   * cv-qualified variants of those types.
template<typename T>
  concept bool 
  Fundamental_type() { return std::is_fundamental<T>::value; }

// Is true if and only if T is a scalar types. The scalar types include
//
// * arithmetic types
// * enumeration types
// * object pointer types
// * member pointer types
// * nullptr_t
// * cv-qualified variants of those types.
template<typename T>
  concept bool 
  Scalar_type() { return std::is_scalar<T>::value; }


// Is true if and only if T is an object type. The object types include
//
// * scalar types
// * array types
// * class types
// * union types
template<typename T>
  concept bool 
  Object_type() { return std::is_object<T>::value; }

// Is true if T is a compound type. The compound types include:
//
// ...
template<typename T>
  concept bool 
  Compound_type() { return std::is_compound<T>::value; }

// Is true if T is a member pointer type.
template<typename T>
  concept bool 
  Member_pointer_type() { 
    return std::is_member_pointer<T>::value; 
  }


// Type properties
// TODO: Finish implementing type properties

// Is true if and only if T is a const-qualified type.
template<typename T>
  concept bool 
  Const_type() { return std::is_const<T>::value; }

// Is true if and only if T is a volatile-qualified type.
template<typename T>
  concept bool 
  Volatile_type() { return std::is_volatile<T>::value; }

// Is true if and only if T is cv-qualified.
template<typename T>
  concept bool 
  Qualified_type() { 
    return Const_type<T>() || Volatile_type<T>(); 
  }

// Is true if and only if T is a trivially copy constructible type.
// template<typename T>
//   concept bool
//   Trivially_copyable_type() { return std::is_trivially_copyable<T>::value; }

// Is true if and only if T is a trivial type.
template<typename T>
  concept bool 
  Trivial_type() { return std::is_trivial<T>::value; }

// Is true if and only if T is a standard layout type.
template<typename T>
  concept bool
  Standard_layout_type() { return __is_standard_layout(T); }

// Is true if and only if T is a plain old data (POD) type.
template<typename T>
  concept bool
  Pod_type() { return __is_pod(T); }

// Is true if and only if T is a literal type.
template<typename T>
  concept bool
  Literal_type() { return __is_literal_type(T); }

// Is true if and only if T is an empty type.
template<typename T>
  concept bool
  Empty_type() { return __is_empty(T); }

// Is true if and only if T is a polymorphic type.
template<typename T>
  concept bool
  Polymorphic_type() { return __is_polymorphic(T); }

// Is true if and only if T is an abstract type.
template<typename T>
  concept bool
  Abstract_type() { return __is_abstract(T); }

// Is true if and only if T is a signed arithmetic type.
template<typename T>
  concept bool
  Signed_type() { return std::is_signed<T>::value; }

// Is true if and only if T is an unsigned integral type.
template<typename T>
  concept bool
  Unsigned_type() { return std::is_unsigned<T>::value; }


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

// ... More traits

// Decay
template<typename T>
  using Decay = typename std::decay<T>::type;


namespace core_impl {
// Strip references and qualifiers from T.
//
// TODO: Are there any other types that we can't allow to decay?
template<typename T>
  struct strip_refquals : std::decay<T> { };

template<typename T>
  struct strip_refquals<T[]> { using type = T[]; };

template<typename T, std::size_t N>
  struct strip_refquals<T[N]> { using type = T[N]; };

template<typename R, typename... Ts>
  struct strip_refquals<R(Ts...)> { using type = R(Ts...); };

template<typename T>
  using strip = typename strip_refquals<T>::type;
} // namespace core_impl

/// For any type T, returns a non-qualified, non-reference type U. This
/// facility is primarily intended to remove qualifiers and references
/// that appear in forwarded arguments.
template<typename T>
  using Strip = core_impl::strip<T>;

} // namespace origin

#endif
