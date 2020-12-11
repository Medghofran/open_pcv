cmake_minimum_required(VERSION 3.10)
# PROJECT METADATA
project(open-pcv CXX)
include(cmake/prevent_insrc_builds.cmake)
include(cmake/standard_project_settings.cmake)

if(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
  option(ENABLE_BUILD_WITH_TIME_TRACE "Enable -ftime-trace to generate time tracing .json files on clang" OFF)
  if(ENABLE_BUILD_WITH_TIME_TRACE)
    add_compile_definitions(project_options INTERFACE -ftime-trace)
  endif()
endif()

# enable doxygen
include(cmake/enable_doxygen.cmake)
enable_doxygen()

# global project options
option(ENABLE_TESTS "Enable Test Builds" ON)

# build and run tests
if(ENABLE_TESTS)
  add_subdirectory(tests)
endif()

# option: execute CLANG-TIDY
option(STATIC_ANALYSIS "RUN CODE ANALYSIS" OFF)
# if clang-tidy is available, use it to clean up the code
if(STATIC_ANALYSIS)
  message(STATUS "Running code analysis on solution")
  find_program(CLANG_TIDY_EXE NAMES "clang-tidy-10")
  if(CLANG_TIDY_EXE)
    message(STATUS "Found clang-tidy: ${CLANG_TIDY_EXE}")
    set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE}" "--fix-errors")
    # set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE}"
    # "--checks=modernize-*,-modernize-use-trailing-return-type" "-fix")
  endif(CLANG_TIDY_EXE)
endif(STATIC_ANALYSIS)

# add source directory
add_subdirectory(src)
