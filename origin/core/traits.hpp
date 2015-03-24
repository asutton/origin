// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#ifndef ORIGIN_CORE_TRAITS_HPP
#define ORIGIN_CORE_TRAITS_HPP

#include <type_traits>

namespace origin 
{

// A helper function used to create rvalues from local
// parameters. This is not defined and never used outside
// of unevaluated operands.
template<typename T> typename std::add_rvalue_reference<T>::type rvalue(T const&);


// A helper function used to create decayed values
// from arguments of various types. This is not defined
// and never used outside of unevaluated operands.
template<typename T> typename std::decay<T>::type decay(T&&);


// -------------------------------------------------------------------------- //
// Primary type categories                                    [trait.primary] //


namespace core
{

// is void
template<typename T> 
struct is_void_impl : std::false_type { };

template<> 
struct is_void_impl<void> : std::true_type { };

template<typename T> 
struct is_void
  : is_void_impl<typename std::remove_cv<T>::type>
{ };


// is narrow character
template<typename T>
struct is_narrow_character_impl : std::false_type { };

template<typename T>
  requires __is_same_as(T, char) 
        || __is_same_as(T, signed char)
        || __is_same_as(T, unsigned char)
struct is_narrow_character_impl<T> : std::true_type { };

template<typename T>
struct is_narrow_character
  : is_narrow_character_impl<typename std::remove_cv<T>::type>
{ };


// is character type
template<typename T>
struct is_character_impl : std::false_type { };

template<typename T>
  requires __is_same_as(T, char) 
        || __is_same_as(T, signed char)
        || __is_same_as(T, unsigned char)
        || __is_same_as(T, char16_t)
        || __is_same_as(T, char32_t)
        || __is_same_as(T, wchar_t)
struct is_character_impl<T> : std::true_type { };

template<typename T>
struct is_character
  : is_character_impl<typename std::remove_cv<T>::type>
{ };


// is signed integer
template<typename T>
struct is_signed_integer_impl : std::false_type { };

template<typename T>
  requires __is_same_as(T, signed char) 
        || __is_same_as(T, short int)
        || __is_same_as(T, int)
        || __is_same_as(T, long int)
        || __is_same_as(T, long long int)
struct is_signed_integer_impl<T> : std::true_type { };

template<typename T>
struct is_signed_integer
  : is_signed_integer_impl<typename std::remove_cv<T>::type>
{ };


// is signed integer
template<typename T>
struct is_unsigned_integer_impl : std::false_type { };

template<typename T>
  requires __is_same_as(T, unsigned char) 
        || __is_same_as(T, unsigned short int)
        || __is_same_as(T, unsigned int)
        || __is_same_as(T, unsigned long int)
        || __is_same_as(T, unsigned long long int)
struct is_unsigned_integer_impl<T> : std::true_type { };

template<typename T>
struct is_unsigned_integer
  : is_unsigned_integer_impl<typename std::remove_cv<T>::type>
{ };


// is bool
template<typename T> 
struct is_bool_impl : std::false_type { };

template<> 
struct is_bool_impl<bool> : std::true_type { };

template<typename T> 
struct is_bool
  : is_bool_impl<typename std::remove_cv<T>::type>
{ };


// is floating point
template<typename T>
struct is_floating_point_impl : std::false_type { };

template<typename T>
  requires __is_same_as(T, float) 
        || __is_same_as(T, double)
        || __is_same_as(T, long double)
struct is_floating_point_impl<T> : std::true_type { };

template<typename T>
struct is_floating_point
  : is_floating_point_impl<typename std::remove_cv<T>::type>
{ };

} // namespace core


// This concept is satisfied by the `void` type
// and cv-qualified versions of that type.
template<typename T>
concept bool 
Void_type() 
{ 
  return core::is_void<T>::value;
}


// The narrow character types are char, signed char, 
// unsigned char, and cv-qualifed versions of those
// types.
template<typename T>
concept bool
Narrow_character_type()
{
  return core::is_narrow_character<T>::value;
}


// The character types are the narrow character types,
// char16_t, char32_t, wchar_t, and cv-qualified
// versions of those types.
//
// Note:
//
// This category is not defined by the standard. It is
// defined here because it is useful in the definition
// of the integral types.
template<typename T>
concept bool
Character_type()
{
  return core::is_character<T>::value;
}


// The signed integer types are signed char, short int, 
// int, long int, and long long int, and cv-qualified
// versions of those types.
template<typename T>
concept bool
Signed_integer_type()
{
  return core::is_signed_integer<T>::value;
}


// For each signed integer type, there is an unsigned
// integer type. These are unsigned char, unsigned short 
// int, unisigned int, unsigned long it, and unsigned 
// long long int, and cv-qualified versions of those
// types.
template<typename T>
concept bool
Unsigned_inetger_type()
{
  return core::is_unsigned_integer<T>::value;
}


// The integral types include bool, the character 
// types, the signed and unsigned integral type, and
// cv-qualified versions of those types.
template<typename T>
concept bool
Integral_type()
{
  return core::is_bool<T>::value
      || core::is_character<T>::value
      || core::is_signed_integer<T>()
      || core::is_unsigned_integer<T>();
}


// The floating point types are float, double, long
// double, and cv-qualified versions of those types.
template<typename T>
concept bool
Floating_point_type()
{
  return core::is_floating_point<T>::value;
}


// Is true if and only if T is an array type of known or unknown 
// bounds. Array types include those with the following form:
//
//    - `T[]`
//    - `T[M]`
//
// where `T` is a type and `N` is an integral constant expression.
template<typename T>
concept bool 
Array_type() 
{ 
  return std::is_array<T>::value; 
}


// Is true if and only if T is an object pointer type. Note that is
// false for member object pointers.
template<typename T>
concept bool 
Pointer_type() 
{ 
  return std::is_pointer<T>::value; 
}


// Is true if and only if T is an lvalue reference type.
template<typename T>
concept bool 
Lvalue_reference_type() 
{ 
  return std::is_lvalue_reference<T>::value; 
}


// Is true if and only if T is an rvalue reference type.
template<typename T>
concept bool 
Rvalue_reference_type() 
{ 
  return std::is_rvalue_reference<T>::value; 
}


// Is true if and only if T is a pointer to a member object.
template<typename T>
concept bool 
Member_object_pointer_type() 
{
  return std::is_member_object_pointer<T>::value; 
}


// Is true if and only if T is a pointer to a member function.
template<typename T>
concept bool 
Member_function_pointer_type() 
{
  return std::is_member_function_pointer<T>::value; 
}


// The enumeration types include all declared using
// the form `enum { ... }`.
template<typename T>
concept bool 
Enum_type() 
{ 
  return __is_enum(T); 
}


// The union types include all those declared using
// the form `union { ... }`.
template<typename T>
concept bool 
Union_type() 
{ 
  return __is_union(T); 
}


// The union types include all those declared using
// the form `struct { ... }` or `class { ... }`.
template<typename T>
concept bool 
Class_type() 
{ 
  return __is_class(T); 
}


// The function types include the types of all functions, 
// which have the form `Result(Args...)` where `Result` 
// is a type and `Args...` is a (possibly empty) sequence 
// of types.
template<typename T>
concept bool 
Function_type() 
{ 
  return std::is_function<T>::value; 
}


// Composite type categories

// Is true if and only T is a reference type. A reference type is either 
// an lvalue or rvalue reference type.
template<typename T>
concept bool 
Reference_type() 
{
  return Lvalue_reference_type<T>() || Rvalue_reference_type<T>();
}


// The arithmetic types are the integral types and
// the floating point types.
template<typename T>
concept bool 
Arithmetic_type() 
{
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


// -------------------------------------------------------------------------- //
//                            Relations on types

namespace core
{
// Heavy lifting for determining convertibility when the
// types are not void.
template<typename T, typename U>
concept bool is_convertible_no_void()
{
  return requires (T t) { {t} -> U; };
}

// Whenever we can't determine convertibility by constraints,
// delegate the standard type trait. This should be rare.
template<typename T, typename U>
struct is_convertible : std::is_convertible<T, U> { };

template<typename T, typename U>
  requires is_convertible_no_void<T, U>()
struct is_convertible<T, U> : std::true_type { };

} // namespace core

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
