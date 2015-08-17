// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#ifndef ORIGIN_CORE_TYPE_HPP
#define ORIGIN_CORE_TYPE_HPP

// The type module defines facilities for debugging
// type issues. In particular, it defines a facility
// `typestr` that returns a human readable representation
// of a type.

#include <string>
#include <typeinfo>


namespace origin {

std::string typestr(std::type_info const& info);


// Helper types.
namespace core {

template<typename... Args> 
struct typestr_dispatch;

template<typename T> 
struct type_to_string;

template<typename T>
struct type_to_string;

template<typename... Args> 
struct typelist_to_string;

} // namespace core



// -------------------------------------------------------------------------- //
// Typestr                                                         [lib.typestr]
//
// Return the textual representation of a type. There are two overloads of
// this function:
//
//    typestr<Args...>()
//    typestr(args...);
//
// The first returns a string containing the names of the explicitly specified
// type arguments. 
//
// The second returns the types of the given arguments. Note that the string
// returned from second overload will reflect the type deduction rules for
// perfect forwarding; lvalues arguments will be result in references, and
// rvalues in unqualified value types.
//
// When multiple arguments are given, the resulting string is written in
// initializer list format: `{T1, T2, ...}`.
template<typename... Args>
inline std::string 
typestr() 
{
  return core::typestr_dispatch<Args...>{}();
}


// Returns the string representation of the types in
// `args...`.
template<typename... Args>
inline std::string 
typestr(Args&&...) 
{
  return typestr<Args...>();
}


namespace core
{
// The typestr dispatcher is used to format type sequences. If multiple types
// are given, the dispatcher will generate the string "{T1, T2, ...}". If a 
// single type is given, the result is just the name of the type.
template<typename... Args>
struct typestr_dispatch 
{
  std::string operator()() const { return typelist_to_string<Args...>{}(); }
};
 

// Specialization matching a single type.
template<typename T>
struct typestr_dispatch<T> 
{
  std::string operator()() const 
  { 
    return type_to_string<T>{}(); 
  }
};

  
// Return the string represntation of the main type T.
template<typename T>
struct type_to_string 
{
  std::string operator()() const 
  { 
    return typestr(typeid(T)); 
  }
};

  
// Return the string representation of the const type T.
template<typename T>
struct type_to_string<const T> 
{
  std::string operator()() const 
  {
    return typestr<T>() + " const";
  }
};


// Return the string representation of the volatile type T.
template<typename T>
struct type_to_string<volatile T> 
{
  std::string operator()() const 
  {
    return typestr<T>() + " volatile";
  }
};


// Return the string representation of the cv-qualified type T.
template<typename T>
struct type_to_string<const volatile T> 
{
  std::string operator()() const 
  {
    return typestr<T>() + " const volatile";
  }
};


// Return the string representation of pointer types.
template<typename T>
struct type_to_string<T*> 
{
  std::string operator()() const 
  {
    return typestr<T>() + "*";
  }
};


// Return the string represntation for lvalue-reference types.
template<typename T>
struct type_to_string<T&> 
{
  std::string operator()() const 
  {
    return typestr<T>() + "&";
  }
};


// Return the string represntation for rvalue-referece types.
template<typename T>
struct type_to_string<T&&> 
{
  std::string operator()() const 
  {
    return typestr<T>() + "&&";
  }
};


// Return the string representation of function paramter lists.
template<typename... Args>
inline std::string 
function_args_to_string() 
{
  return '(' + typelist_to_string<Args...>{}() + ')';
}


// Return the string representation of a function type.
template<typename R, typename... Args>
struct type_to_string<R(Args...)> 
{
  std::string operator()() const 
  {
    return typestr<R>() + function_args_to_string<Args...>();
  }
};


// Return the string representation of a function pointer type.
template<typename R, typename... Args>
struct type_to_string<R(*)(Args...)> 
{
  std::string operator()() const 
  {
    return typestr<R>() + "(*)" + function_args_to_string<Args...>();
  }
};


// Return the string representation of an array of unknown bounds type.
template<typename T>
struct type_to_string<T[]> 
{
  std::string operator()() const 
  {
    return typestr<T>() + "[]";
  }
};


// Return the string representation of an array of known bounds type.
template<typename T, std::size_t N>
struct type_to_string<T[N]> 
{
  std::string operator()() const 
  {
    return typestr<T>() + '[' + std::to_string(N) + ']';
  }
};


// Return the string representation of an reference to array of known 
// bounds type.
template<typename T, std::size_t N>
struct type_to_string<T(&)[N]> 
{
  std::string operator()() const 
  {
    return typestr<T>() + "(&)" + '[' + std::to_string(N) + ']';
  }
};


// Return the string representation of a list of types.
template<typename T, typename... Args>
struct typelist_to_string<T, Args...> 
{
  std::string operator()() const 
  {
    return typestr<T>() + ", " + typelist_to_string<Args...>{}();
  }
};


// Return the string representation of a list of types (single type).
template<typename T>
struct typelist_to_string<T> 
{
  std::string operator()() const 
  { 
    return typestr<T>(); 
  }
};


// Return the string representation of a list of types (empty list).
template<>
struct typelist_to_string<> 
{
    std::string operator()() const 
    { 
      return std::string{}; 
    }
};


} // namespace core

} // namespace origin


#endif
