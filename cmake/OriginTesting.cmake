#.rst:
# OriginTesting
# -------------
#
# Convenience macros for adding compilation and execution tests to a project
# to be run by :manual:`ctest(1)`.
#
# ::
#
#   generate_compile_test_driver(<file>)
#
# Generates a CMake script file that can be used as the project's test driver
# for compilation testing, suitable for passing to :command:`add_test`'s
# ``COMMAND`` argument. If ``<file>`` is a relative path, it is evaluated
# with respect to the project binary directory. The full path to the
# generated CMake script file is stored in the variable
# ``COMPILE_TEST_DRIVER``.
#
# .. note::
#
#    ``generate_compile_test_driver()`` must be invoked before invoking
#    either ``add_compile_test()`` or ``add_run_test()``.
#
# Example usage:
#
# .. code-block:: cmake
#
#    generate_compile_test_driver(CompileTestDriver.cmake)
#    add_executable(myexe myexe.cpp)
#    add_test(NAME mytest
#             COMMAND ${CMAKE_COMMAND} -P ${COMPILE_TEST_DRIVER} $<CONFIG> myexe)
#
# This generates a file named ``CompileTestDriver.cmake`` in
# ``${PROJECT_BINARY_DIR}``, then adds to the project an executable target
# ``myexe`` and creates a test ``mytest`` whose command runs the compilation
# test driver passing the configuration name and the name of the executable
# target ``myexe``.
#
# ::
#
#   add_compile_test(BASE_NAME <base_name> SOURCES source1 [source2...]
#                    [WIN32] [MACOSX_BUNDLE]
#                    [CONFIGURATIONS <config>...]
#                    [WORKING_DIRECTORY <dir>])
#
# Invokes :command:`add_executable` to add a test program called
# ``test_<base_name>`` that is built from the given source files, and then
# invokes :command:`add_test` to add a test called ``compile_<base_name>``
# that executes the compilation test driver script with the target
# ``test_<base_name>``.
#
# Supported options:
#
# ``BASE_NAME``
#   Determines the name of the test that is added to the project.
# ``SOURCES``
#   Specifies a list of source files to be passed to the
#   :command:`add_executable` command.
# ``WIN32``
#   Corresponds to the ``WIN32`` option for the :command:`add_executable`
#   command.
# ``MACOSX_BUNDLE``
#   Corresponds to the ``MACOSX_BUNDLE`` option for the
#   :command:`add_executable` command.
# ``CONFIGURATIONS``
#   Specifies the ``CONFIGURATIONS`` arguments that are passed to the
#   :command:`add_test` command.
# ``WORKING_DIRECTORY``
#   Specifies the ``WORKING_DIRECTORY`` argument that is passed to the
#   :command:`add_test` command.
#
# ::
#
#   add_compile_test(<base_name> source1 [source2...])
#
# A shorter form of the above.
#
# ::
#
#   add_run_test(BASE_NAME <base_name> SOURCES source1 [source2...]
#                [WIN32] [MACOSX_BUNDLE]
#                [CONFIGURATIONS <config>...]
#                [WORKING_DIRECTORY <dir>])
#
# Invokes :command:`add_executable` to add a test program called
# ``test_<base_name>`` that is built from the given source files, and then
# invokes :command:`add_test` to add a test called ``compile_<base_name>``
# that executes the compilation test driver script with the target
# ``test_<base_name>``. Lastly, :command:`add_test` is invoked to add a test
# that executes the aforementioned test program.
#
# Supported options:
#
# ``BASE_NAME``
#   Determines the names of the tests that are added to the project.
# ``SOURCES``
#   Specifies a list of source files to be passed to the
#   :command:`add_executable` command.
# ``WIN32``
#   Corresponds to the ``WIN32`` option for the :command:`add_executable`
#   command.
# ``MACOSX_BUNDLE``
#   Corresponds to the ``MACOSX_BUNDLE`` option for the
#   :command:`add_executable` command.
# ``CONFIGURATIONS``
#   Specifies the ``CONFIGURATIONS`` arguments that are passed to the
#   :command:`add_test` command.
# ``WORKING_DIRECTORY``
#   Specifies the ``WORKING_DIRECTORY`` argument that is passed to the
#   :command:`add_test` command.
#
# ::
#
#   add_run_test(<base_name> source1 [source2...])
#
# A shorter form of the above.
#
# Requires CMake 2.8.3 or later.

include(CMakeParseArguments)

get_filename_component(_ORIGIN_TESTING_MODULE_DIR ${CMAKE_CURRENT_LIST_FILE} PATH)

function(GENERATE_COMPILE_TEST_DRIVER FILE)
  if(NOT IS_ABSOLUTE ${FILE})
    set(FILE ${PROJECT_BINARY_DIR}/${FILE})
  endif()
  set(COMPILE_TEST_DRIVER ${FILE}
    CACHE INTERNAL "Path to the compilation test driver script.")
  configure_file(${_ORIGIN_TESTING_MODULE_DIR}/CompileTestDriver.cmake.in
    ${COMPILE_TEST_DRIVER} @ONLY)
endfunction()

macro(ADD_COMPILE_TEST)
  set(options WIN32 MACOSX_BUNDLE)
  set(oneValueArgs BASE_NAME WORKING_DIRECTORY)
  set(multiValueArgs SOURCES CONFIGURATIONS)

  cmake_parse_arguments(_ADD_COMPILE_TEST "${options}" "${oneValueArgs}"
    "${multiValueArgs}" ${ARGN})

  set(_ADD_COMPILE_TEST_ADD_WIN32)
  set(_ADD_COMPILE_TEST_ADD_MACOSX_BUNDLE)
  set(_ADD_COMPILE_TEST_ADD_CONFIGURATIONS)
  set(_ADD_COMPILE_TEST_ADD_WORKING_DIRECTORY)

  if(NOT (DEFINED _ADD_COMPILE_TEST_BASE_NAME
          OR DEFINED _ADD_COMPILE_TEST_SOURCES))
    if(${ARGC} LESS 2)
      message(FATAL_ERROR "ADD_COMPILE_TEST() called with incorrect number of arguments.")
    endif()
    # Parse arguments for alternate signature.
    set(_ADD_COMPILE_TEST_BASE_NAME ${ARGV0})
    set(_ADD_COMPILE_TEST_SOURCES ${ARGV})
    list(REMOVE_AT _ADD_COMPILE_TEST_SOURCES 0)
  else()
    if(DEFINED _ADD_COMPILE_TEST_UNPARSED_ARGUMENTS)
      message(FATAL_ERROR "ADD_COMPILE_TEST() given unknown keywords \"${_ADD_COMPILE_TEST_UNPARSED_ARGUMENTS}\".")
    endif()
    if(_ADD_COMPILE_TEST_WIN32)
      set(_ADD_COMPILE_TEST_ADD_WIN32 WIN32)
    endif()
    if(_ADD_COMPILE_TEST_MACOSX_BUNDLE)
      set(_ADD_COMPILE_TEST_ADD_MACOSX_BUNDLE MACOSX_BUNDLE)
    endif()
    if(_ADD_COMPILE_TEST_CONFIGURATIONS)
      set(_ADD_COMPILE_TEST_ADD_CONFIGURATIONS
        CONFIGURATIONS ${_ADD_COMPILE_TEST_CONFIGURATIONS})
    endif()
    if(_ADD_COMPILE_TEST_WORKING_DIRECTORY)
      set(_ADD_COMPILE_TEST_ADD_WORKING_DIRECTORY
        WORKING_DIRECTORY ${_ADD_COMPILE_TEST_WORKING_DIRECTORY})
    endif()
  endif()

  if(_ADD_COMPILE_TEST_BASE_NAME STREQUAL "")
    message(FATAL_ERROR "ADD_COMPILE_TEST() must be given non-empty BASE_NAME.")
  endif()
  if(_ADD_COMPILE_TEST_SOURCES STREQUAL "")
    message(FATAL_ERROR "ADD_COMPILE_TEST() must be given non-empty SOURCES.")
  endif()

  set(_ADD_COMPILE_TEST_TARGET_EXECUTABLE test_${_ADD_COMPILE_TEST_BASE_NAME})
  set(_ADD_COMPILE_TEST_NAME compile_${_ADD_COMPILE_TEST_BASE_NAME})

  # Add test program as an executable target.
  add_executable(${_ADD_COMPILE_TEST_TARGET_EXECUTABLE}
    ${_ADD_COMPILE_TEST_ADD_WIN32} ${_ADD_COMPILE_TEST_ADD_MACOSX_BUNDLE}
    EXCLUDE_FROM_ALL ${_ADD_COMPILE_TEST_SOURCES})
  # Add test that invokes the compilation test driver script.
  add_test(NAME ${_ADD_COMPILE_TEST_NAME}
    COMMAND ${CMAKE_COMMAND} -P ${COMPILE_TEST_DRIVER}
      $<CONFIG> ${_ADD_COMPILE_TEST_TARGET_EXECUTABLE}
    ${_ADD_COMPILE_TEST_ADD_CONFIGURATIONS}
    ${_ADD_COMPILE_TEST_ADD_WORKING_DIRECTORY})
  set_tests_properties(${_ADD_COMPILE_TEST_NAME} PROPERTIES
    REQUIRED_FILES ${COMPILE_TEST_DRIVER})
endmacro()

macro(ADD_RUN_TEST)
  set(options WIN32 MACOSX_BUNDLE)
  set(oneValueArgs BASE_NAME WORKING_DIRECTORY)
  set(multiValueArgs SOURCES CONFIGURATIONS)

  cmake_parse_arguments(_ADD_RUN_TEST "${options}" "${oneValueArgs}"
    "${multiValueArgs}" ${ARGN})

  set(_ADD_RUN_TEST_ADD_WIN32)
  set(_ADD_RUN_TEST_ADD_MACOSX_BUNDLE)
  set(_ADD_RUN_TEST_ADD_CONFIGURATIONS)
  set(_ADD_RUN_TEST_ADD_WORKING_DIRECTORY)

  if(NOT (DEFINED _ADD_RUN_TEST_BASE_NAME OR DEFINED _ADD_RUN_TEST_SOURCES))
    if(${ARGC} LESS 2)
      message(FATAL_ERROR "ADD_RUN_TEST() called with incorrect number of arguments.")
    endif()
    # Parse arguments for alternate signature.
    set(_ADD_RUN_TEST_BASE_NAME ${ARGV0})
    set(_ADD_RUN_TEST_SOURCES ${ARGV})
    list(REMOVE_AT _ADD_RUN_TEST_SOURCES 0)
  else()
    if(DEFINED _ADD_RUN_TEST_UNPARSED_ARGUMENTS)
      message(FATAL_ERROR "ADD_RUN_TEST() given unknown keywords \"${_ADD_RUN_TEST_UNPARSED_ARGUMENTS}\".")
    endif()
    if(_ADD_RUN_TEST_WIN32)
      set(_ADD_RUN_TEST_ADD_WIN32 WIN32)
    endif()
    if(_ADD_RUN_TEST_MACOSX_BUNDLE)
      set(_ADD_RUN_TEST_ADD_MACOSX_BUNDLE MACOSX_BUNDLE)
    endif()
    if(_ADD_RUN_TEST_CONFIGURATIONS)
      set(_ADD_RUN_TEST_ADD_CONFIGURATIONS
        CONFIGURATIONS ${_ADD_RUN_TEST_CONFIGURATIONS})
    endif()
    if(_ADD_RUN_TEST_WORKING_DIRECTORY)
      set(_ADD_RUN_TEST_ADD_WORKING_DIRECTORY
        WORKING_DIRECTORY ${_ADD_RUN_TEST_WORKING_DIRECTORY})
    endif()
  endif()

  if(_ADD_RUN_TEST_BASE_NAME STREQUAL "")
    message(FATAL_ERROR "ADD_RUN_TEST() must be given non-empty BASE_NAME.")
  endif()
  if(_ADD_RUN_TEST_SOURCES STREQUAL "")
    message(FATAL_ERROR "ADD_RUN_TEST() must be given non-empty SOURCES.")
  endif()

  set(_ADD_RUN_TEST_TARGET_EXECUTABLE test_${_ADD_RUN_TEST_BASE_NAME})
  set(_ADD_COMPILE_TEST_NAME compile_${_ADD_RUN_TEST_BASE_NAME})
  set(_ADD_RUN_TEST_NAME run_${_ADD_RUN_TEST_BASE_NAME})

  # Add test program as an executable target.
  add_executable(${_ADD_RUN_TEST_TARGET_EXECUTABLE}
    ${_ADD_RUN_TEST_ADD_WIN32} ${_ADD_RUN_TEST_ADD_MACOSX_BUNDLE}
    EXCLUDE_FROM_ALL ${_ADD_RUN_TEST_SOURCES})
  # Add test that invokes the compilation test driver script.
  add_test(NAME ${_ADD_COMPILE_TEST_NAME}
    COMMAND ${CMAKE_COMMAND} -P ${COMPILE_TEST_DRIVER}
      $<CONFIG> ${_ADD_RUN_TEST_TARGET_EXECUTABLE}
    ${_ADD_RUN_TEST_ADD_CONFIGURATIONS}
    ${_ADD_RUN_TEST_ADD_WORKING_DIRECTORY})
  set_tests_properties(${_ADD_COMPILE_TEST_NAME} PROPERTIES
    REQUIRED_FILES ${COMPILE_TEST_DRIVER})
  # Add test that invokes the test program.
  add_test(NAME ${_ADD_RUN_TEST_NAME}
    COMMAND ${_ADD_RUN_TEST_TARGET_EXECUTABLE}
    ${_ADD_RUN_TEST_ADD_CONFIGURATIONS}
    ${_ADD_RUN_TEST_ADD_WORKING_DIRECTORY})
  set_tests_properties(${_ADD_RUN_TEST_NAME} PROPERTIES
    DEPENDS ${_ADD_COMPILE_TEST_NAME})
endmacro()
