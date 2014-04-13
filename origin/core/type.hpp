// Copyright (c) 2008-2014 Andrew Sutton
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#ifndef ORIGIN_CORE_TYPE_HPP
#define ORIGIN_CORE_TYPE_HPP


#if defined(__GNUC__)
#include <cxxabi.h>
#endif

#include <cstring>
#include <string>

namespace origin {

namespace type_impl {
  template <typename... Args> 
    struct typestr_dispatch;
  
  template <typename T> 
    struct type_to_string;
  
  template <typename T>
    struct type_to_string;

  template <typename... Args> 
    struct typelist_to_string;
  
  std::string to_string(const std::type_info& info);
} // namespace type_impl


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
// initializer list format: "{T1, T2, ...}".
template <typename... Args>
  inline std::string typestr() {
    return type_impl::typestr_dispatch<Args...>{}();
  }
  
template <typename... Args>
  inline std::string typestr(Args&&...) {
    return typestr<Args...>();
  }

namespace type_impl
{
  // The typestr dispatcher is used to format type sequences. If multiple types
  // are given, the dispatcher will generate the string "{T1, T2, ...}". If a 
  // single type is given, the result is just the name of the type.
  template <typename... Args>
    struct typestr_dispatch {
      std::string operator()() const {
        return typelist_to_string<Args...>{}();
      }
    };
    
  template <typename T>
    struct typestr_dispatch<T> {
      std::string operator()() const {
        return type_to_string<T>{}();
      }
    };

    
  // Return the string represntation of the main type T.
  template <typename T>
    struct type_to_string {
      std::string operator()() const {
        return to_string(typeid(T));
      }
    };
    
  // Return the string representation of the const type T.
  template <typename T>
    struct type_to_string<const T> {
      std::string operator()() const {
        return "const " + typestr<T>();
      }
    };

  // Return the string representation of the volatile type T.
  template <typename T>
    struct type_to_string<volatile T> {
      std::string operator()() const {
        return "volatile " + typestr<T>();
      }
    };

  // Return the string representation of the cv-qualified type T.
  template <typename T>
    struct type_to_string<const volatile T> {
      std::string operator()() const {
        return "const volatile " + typestr<T>();
      }
    };

  // Return the string representation of pointer types.
  template <typename T>
    struct type_to_string<T*> {
      std::string operator()() const {
        return typestr<T>() + "*";
      }
    };


  // Return the string represntation for const pointer types.
  template <typename T>
    struct type_to_string<T* const> {
      std::string operator()() const {
        return typestr<T>() + "* const";
      }
    };

  // Return the string represntation for volatile pointer types.
  template <typename T>
    struct type_to_string<T* volatile> {
      std::string operator()() const {
        return typestr<T>() + "* volatile";
      }
    };

  // Return the string represntation for cv-qualified pointer types.
  template <typename T>
    struct type_to_string<T* const volatile> {
      std::string operator()() const {
        return typestr<T>() + "* const volatile";
      }
    };

  // Return the string represntation for lvalue-reference types.
  template <typename T>
    struct type_to_string<T&> {
      std::string operator()() const {
        return typestr<T>() + "&";
      }
    };

  // Return the string represntation for rvalue-referece types.
  template <typename T>
    struct type_to_string<T&&> {
      std::string operator()() const {
        return typestr<T>() + "&&";
      }
    };

  // Return the string representation of function paramter lists.
  template <typename... Args>
    inline std::string 
    function_args_to_string() {
      return '(' + typelist_to_string<Args...>{}() + ')';
    }


  // Return the string representation of a function type.
  template <typename R, typename... Args>
    struct type_to_string<R(Args...)> {
      std::string operator()() const {
        return typestr<R>() + function_args_to_string<Args...>();
      }
    };

  // Return the string representation of a function pointer type.
  template <typename R, typename... Args>
    struct type_to_string<R(*)(Args...)> {
      std::string operator()() const {
        return typestr<R>() + "(*)" + function_args_to_string<Args...>();
      }
    };

  // Return the string representation of an array of unknown bounds type.
  template <typename T>
    struct type_to_string<T[]> {
      std::string operator()() const {
        return typestr<T>() + "[]";
      }
    };

  // Return the string representation of an array of known bounds type.
  template <typename T, std::size_t N>
    struct type_to_string<T[N]> {
      std::string operator()() const {
        return typestr<T>() + '[' + std::to_string(N) + ']';
      }
    };

  // Return the string representation of an reference to array of known 
  // bounds type.
  template <typename T, std::size_t N>
    struct type_to_string<T(&)[N]> {
      std::string operator()() const {
        return typestr<T>() + "(&)" + '[' + std::to_string(N) + ']';
      }
    };


  // Return the string representation of a list of types.
  template <typename T, typename... Args>
    struct typelist_to_string<T, Args...> {
      std::string operator()() const {
        return typestr<T>() + ", " + typelist_to_string<Args...>{}();
      }
    };

  // Return the string representation of a list of types (single type).
  template <typename T>
    struct typelist_to_string<T> {
      std::string operator()() const { return typestr<T>(); }
    };

  // Return the string representation of a list of types (empty list).
  template<>
    struct typelist_to_string<> {
      std::string operator()() const { return std::string{}; }
    };

  // Return the string represntation of a type info object.
#if defined(__GNUC__)
  inline std::string 
  to_string(const std::type_info& info)
  {
    static constexpr std::size_t max_buffer = 8192;
    char buf[max_buffer];
    std::size_t n = max_buffer;
    abi::__cxa_demangle(info.name(), buf, &n, 0); 
    return std::move(std::string(buf, ::strlen(buf)));
  }
#else
# error No compiler support for rendering type names
#endif

} // namespace type_impl


} // namespace origin

#endif
