# Building source dirs
include_directories(${PROJECT_SOURCE_DIR}/include)

find_package(glfw3 REQUIRED)

# for testing purposes only
add_executable(lib lib.cpp utils/windows.cpp)
target_link_libraries(lib glfw)