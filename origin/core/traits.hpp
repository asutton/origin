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
// Language support concepts                                  [concepts.lang] //
//
// There are a small number of concepts inherently tied
// to the language. These include concepts that determine
// when types are equivalent, convertible, and derived, or
// share a common type.


// The `Same` concept requires types `T` and `U` to be 
// equivalent types.
//
// Examples:
//
//    Same<int, int>()       ~> satsified
//    Same<int, int const>() ~> not satisfied
template<typename T, typename U>
concept bool 
Same() 
{ 
  return __is_same_as(T, U); 
}


// A type `T` is convertible to another type `U` an expression
// of type `T` is implicitly convertible to `U`. That is,
// the concept is satisfied if the following declaration is
// well-formed:
//
//    U u = t;
//
// where `t` is an expression of type `T`.
//
// Examples:
//
//    Convertible<int, int>()       ~> satisfied
//    Convertible<int, int const>() ~> satisfied
//    Convertible<int const, int>() ~> not satisfied
//
// Notes:
//
// This cannot be implemented without specializations to 
// handle the void cases. As a result, we delegate to a 
// custom implementation of the trait.
//
// FIXME: The current implmentation in traits.hpp does not
// current implement the full set of cases that the std
// type trait defines.
template<typename T, typename U>
concept bool 
Convertible() 
{
  // return core::is_convertible<T, U>::value;
  return std::is_convertible<T, U>::value;
}


// The `Derived` concept requires type `T` to be derived
// from type `U`. Note that this is not the same as simply
// testing that `U` is a base class of `T`. Expressions
// of type `T` must also be convertible to `U`.
//
// Examples:
//
//    struct B { };
//    struct D1 : B { };
//    class D2 : B { };
//
//    Derived<D1, B>() ~> satsified
//    Derived<D2, B>() ~> not satisfied
template<typename T, typename U>
concept bool 
Derived() 
{
  return __is_base_of(U, T) && Convertible<T, U>();
}


// The `Common_type` alias represents common type of a 
// sequence of type arguments. 
//
// See the definition of std::common_type for details.
template<typename... Ts>
using Common_type = typename std::common_type<Ts...>::type;


// The `Common` concept is satisfied when the common type of
// the sequence `Ts` exists.
template<typename... Ts>
concept bool 
Common() 
{
  return requires { typename Common_type<Ts...>; };
}


// -------------------------------------------------------------------------- //
// Primary type categories                                    [trait.primary] //
//
// These implementation helpers are defined as constexpr 
// functions in order to act as compile-time firewalls
// due to the extensive use of disjunction.



namespace core
{

// Returns true if T is equivalent to U when cv-qualifiers
// are removed from both types.
template<typename T, typename U>
constexpr bool
is_cv_same_as()
{
  return __is_same_as(std::remove_cv_t<T>, std::remove_cv_t<U>);
}


// is void
template<typename T>
constexpr bool 
is_void()
{
  return is_cv_same_as<T, void>();
}


// is bool
template<typename T>
constexpr bool 
is_bool()
{
  return is_cv_same_as<T, bool>();
}


// is narrow character
template<typename T>
constexpr bool
is_narrow_character()
{
  return is_cv_same_as<T, char>()
      || is_cv_same_as<T, signed char>()
      || is_cv_same_as<T, unsigned char>();
}


// is wide character
template<typename T>
constexpr bool
is_wide_character()
{
  return is_cv_same_as<T, char16_t>()
      || is_cv_same_as<T, char32_t>()
      || is_cv_same_as<T, wchar_t>();
}


// is signed integer
template<typename T>
constexpr bool
is_signed_integer()
{
  return is_cv_same_as<T, signed char>()
      || is_cv_same_as<T, short int>()
      || is_cv_same_as<T, int>()
      || is_cv_same_as<T, long int>()
      || is_cv_same_as<T, long long int>();
}


// is signed integer
template<typename T>
constexpr bool
is_unsigned_integer()
{
  return is_cv_same_as<T, unsigned char>()
      || is_cv_same_as<T, unsigned short int>()
      || is_cv_same_as<T, unsigned int>()
      || is_cv_same_as<T, unsigned long int>()
      || is_cv_same_as<T, unsigned long long int>();
}


// is floating point
template<typename T>
constexpr bool
is_floating_point()
{
  return is_cv_same_as<T, float>()
      || is_cv_same_as<T, double>()
      || is_cv_same_as<T, long double>();
}

} // namespace core


// This concept is satisfied by the `void` type
// and cv-qualified versions of that type.
template<typename T>
concept bool 
Void_type() 
{
  return core::is_void<T>();
}


// The narrow character types are char, signed char, 
// unsigned char, and cv-qualifed versions of those
// types.
template<typename T>
concept bool
Narrow_character_type()
{
  return core::is_narrow_character<T>();
}


// The wide character types are char16_t, char32_t,
// wchar_t, and cv-qualified versions of those types.
//
// Note:
//
// This category is not defined by the C++ Standard.
// However, it is helpful for the purpose of defining
// relations between categories of integral types.
template<typename T>
concept bool
Wide_character_type()
{
  return core::is_wide_character<T>();
}


// The narrow and wide character types are collectively
// called the character types.
//
// Note:
//
// This category is not defined by the C++ Standard. 
// However, it is helpful for the purpose of defining
// relations between categories of integral types.
template<typename T>
concept bool
Character_type()
{
  return core::is_narrow_character<T>()
      || core::is_wide_character<T>();
}


// The signed integer types are signed char, short int, 
// int, long int, and long long int, and cv-qualified
// versions of those types.
template<typename T>
concept bool
Signed_integer_type()
{
  return core::is_signed_integer<T>();
}


// For each signed integer type, there is an unsigned
// integer type. These are unsigned char, unsigned short 
// int, unisigned int, unsigned long it, and unsigned 
// long long int, and cv-qualified versions of those
// types.
template<typename T>
concept bool
Unsigned_integer_type()
{
  return core::is_unsigned_integer<T>();
}


// The integral types include bool, the character 
// types, the signed and unsigned integral type, and
// cv-qualified versions of those types.
template<typename T>
concept bool
Integral_type()
{
  return core::is_bool<T>()
      || core::is_narrow_character<T>()
      || core::is_wide_character<T>()
      || core::is_signed_integer<T>()
      || core::is_unsigned_integer<T>();
}


// The floating point types are float, double, long
// double, and cv-qualified versions of those types.
template<typename T>
concept bool
Floating_point_type()
{
  return core::is_floating_point<T>();
}


// Array types include those with the following form:
//
//    - `T[]`
//    - `T[M]`
//
// where `T` is a type and `N` is an integral constant 
// expression.
//
// TODO: Add traits that distinguish between arrays of 
// unknown bound and array of known bound.
template<typename T>
concept bool 
Array_type() 
{ 
  return std::is_array<T>::value; 
}


// A pointer type has the form `T*`.
template<typename T>
concept bool 
Pointer_type() 
{ 
  return std::is_pointer<T>::value; 
}


// An lvalue referencee type has the form `T&`.
template<typename T>
concept bool 
Lvalue_reference_type() 
{ 
  return std::is_lvalue_reference<T>::value; 
}


// An rvalue reference type has the form `T&&`.
template<typename T>
concept bool 
Rvalue_reference_type() 
{ 
  return std::is_rvalue_reference<T>::value; 
}


// A pointer to a member object type has the form
// `T (C::*)`.
template<typename T>
concept bool 
Member_object_pointer_type() 
{
  return std::is_member_object_pointer<T>::value; 
}


// A pointer to a member funtion type has the form
// `T (C::*)(Args...)` where `Args...` is a (possibly
// empty) sequence of parameter types. 
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


// -------------------------------------------------------------------------- //
// Composite type categories                                [trait.composite] //

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


// The fundamental types are the built-in types of the
// programming language and include:
//
//    - void,
//    - nullptr_t,
//    - the arithmetic types, and
//    - cv-qualified variants of those types.
template<typename T>
concept bool 
Fundamental_type() 
{ 
  return std::is_fundamental<T>::value; 
}


// The scalar types are:
//
//    - the arithmetic types,
//    - enumeration types,
//    - pointer types,
//    - object pointer types,
//    - member pointer types,
//    - nullptr_t, and
//    - cv-qualified variants of those types.
template<typename T>
concept bool 
Scalar_type() 
{ 
  return std::is_scalar<T>::value; 
}


// An object type is one whose values can be placed
// in memory. They are:
//
//    - the scalar types,
//    - array types,
//    - class types,
//    - union types, and
//    - cv-qualified variants of those types.
template<typename T>
concept bool 
Object_type() 
{ 
  return std::is_object<T>::value; 
}


// A compound type is one that is comprised of other 
// scalar and compound types.
template<typename T>
concept bool 
Compound_type() 
{ 
  return std::is_compound<T>::value; 
}


// A member pointer type is either a member object
// pointer or member function pointer.
template<typename T>
concept bool 
Member_pointer_type() 
{ 
  return std::is_member_pointer<T>::value; 
}

// -------------------------------------------------------------------------- //
// Type properties                                           [trait.property] //


// A const type has the form `const T`.
template<typename T>
concept bool 
Const_type() 
{ 
  return std::is_const<T>::value; 
}


// A volatile type has the form `volatile T`.
template<typename T>
concept bool 
Volatile_type() 
{ 
  return std::is_volatile<T>::value; 
}


// A qualified type is either a const type or a
// volatile type.
template<typename T>
concept bool 
Qualified_type() 
{ 
  return Const_type<T>() || Volatile_type<T>(); 
}


// A trivial type is one trivially copyable and trivially 
// default constructible.
template<typename T>
concept bool 
Trivial_type() 
{ 
  return std::is_trivial<T>::value; 
}


// A standard layout type is...
template<typename T>
concept bool
Standard_layout_type() 
{ 
  return __is_standard_layout(T); 
}


// A POD (plain old data) type is one whose layout is
// compatible with the C programming language.
template<typename T>
concept bool
Pod_type() 
{ 
  return __is_pod(T); 
}

// A literal type...
template<typename T>
concept bool
Literal_type() 
{ 
  return __is_literal_type(T); 
}


// An empty type defines has no non-static members
// or base classes with non-static members.
template<typename T>
concept bool
Empty_type() 
{ 
  return __is_empty(T); 
}


// A polymorphic type has at least one virtual
// function.
template<typename T>
concept bool
Polymorphic_type() 
{ 
  return __is_polymorphic(T); 
}


// An abstract type has at least one pure virtual
// function.
template<typename T>
concept bool
Abstract_type() 
{ 
  return __is_abstract(T); 
}


// The signed arithmetic types.
template<typename T>
concept bool
Signed_type() 
{ 
  return std::is_signed<T>::value; 
}


// The unsigned arithmetic types.
template<typename T>
concept bool
Unsigned_type() 
{ 
  return std::is_unsigned<T>::value; 
}


// -------------------------------------------------------------------------- //
// Type transformations                                     [trait.transform] //

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


namespace core_impl 
{

// Strip references and qualifiers from T. Decay is
// almost the right transformation, but we want to
// let arrays and functions transform into pointers.
template<typename T>
struct strip_refs_and_quals : std::decay<T> { };


// Preserve array of unknown bound type.
template<typename T>
struct strip_refs_and_quals<T[]> { using type = T[]; };


// Preserve array of known bound type.
template<typename T, std::size_t N>
struct strip_refs_and_quals<T[N]> { using type = T[N]; };


// Preserve function types.
template<typename R, typename... Ts>
struct strip_refs_and_quals<R(Ts...)> { using type = R(Ts...); };


template<typename T>
using strip = typename strip_refs_and_quals<T>::type;

} // namespace core_impl


// For any type T, returns a non-qualified, non-reference 
// type U. This facility is primarily intended to remove 
// qualifiers and references that appear in forwarded arguments.
template<typename T>
using Strip = core_impl::strip<T>;


} // namespace origin


#endif
