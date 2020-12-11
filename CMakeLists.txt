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

if(ENABLE_TESTS)
  add_subdirectory(tests)
endif()

# add source directory
add_subdirectory(src)
