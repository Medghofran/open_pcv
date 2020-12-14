# Building source dirs
include_directories(${PROJECT_SOURCE_DIR}/include)

# set window api options
set(WIN_API "glfw3" CACHE STRING "Window management api for the project")
set_property(
    CACHE WIN_API 
    PROPERTY STRINGS 
    "glfw3" 
    "none")
message(STATUS "WINDOWS API USED: ${WIN_API}")

if(WIN_API MATCHES "glfw3")
    message(STATUS "Looking for dependencies")
    find_package(glfw3 REQUIRED)
endif(WIN_API MATCHES "glfw3")


# for testing purposes only
add_executable(lib lib.cpp utils/windows.cpp)
target_link_libraries(lib glfw)