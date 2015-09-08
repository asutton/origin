#.rst:
# OriginUtilities
# ---------------
#
# Various utility macros and functions.
#
# ::
#
#   string_join(<output variable> <separator> [<input>...])
#
# Concatenates all the input arguments together, using the specified
# separator string between each element. The result is stored in the named
# output variable.
#
# Requires CMake 2.8 or later.

function(STRING_JOIN VARIABLE SEPARATOR)
  set(${VARIABLE})
  if(ARGC GREATER 2)
    list(LENGTH ARGN n)
    math(EXPR n-1 "${n} - 1")
    foreach(i RANGE ${n-1})
      list(GET ARGN ${i} ARG)
      set(${VARIABLE} "${${VARIABLE}}${ARG}")
      if(i LESS n-1)
        set(${VARIABLE} "${${VARIABLE}}${SEPARATOR}")
      endif()
    endforeach()
  endif()
  set(${VARIABLE} ${${VARIABLE}} PARENT_SCOPE)
endfunction()
