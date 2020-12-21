cmake_minimum_required(VERSION 3.10)

# PROJECT METADATA
project(open-pcv CXX)
include(cmake/prevent_insrc_builds.cmake)
include(cmake/standard_project_settings.cmake)

# ENABLE C++17 LANGUAGE STANDARD
set_property(GLOBAL PROPERTY CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

# ENABLE TIME TRACING 
if(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
  option(ENABLE_BUILD_WITH_TIME_TRACE "Enable -ftime-trace to generate time tracing .json files on clang" OFF)
  if(ENABLE_BUILD_WITH_TIME_TRACE)
    add_compile_definitions(project_options INTERFACE -ftime-trace)
  endif()
endif()

# ENABLE DOXYGEN
include(cmake/enable_doxygen.cmake)
enable_doxygen()

# GLOBAL PROJECT OPTIONS
option(ENABLE_TESTS "Enable Test Builds" ON)
option(STATIC_ANALYSIS "RUN CODE ANALYSIS" OFF)

# build and run tests
if(ENABLE_TESTS)
  add_subdirectory(tests)
endif()


# set pcv core path
set(PCV_CORE ${PROJECT_SOURCE_DIR})

# option: execute CLANG-TIDY
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

# ADD SOURCE DIRECTORY
add_subdirectory(src)
