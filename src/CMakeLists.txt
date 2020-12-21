# Building source dirs
include_directories(${PROJECT_SOURCE_DIR}/include)

# library dependencies list
set(PCV_DEPS "")

# set window api options
set(WIN_API
    "glfw3"
    CACHE STRING "Window management API")
set_property(CACHE WIN_API PROPERTY STRINGS "glfw3" "none")

# set rendering api
set(RENDER_API
    "OpenGL"
    CACHE STRING "Rendering API")
set_property(CACHE RENDER_API PROPERTY STRINGS "OpenGL" "none")

if(WIN_API MATCHES "glfw3")
  message(STATUS "Looking for glfw dependencies")
  find_package(glfw3 REQUIRED)
  list(APPEND PCV_DEPS "glfw")
endif(WIN_API MATCHES "glfw3")

if(RENDER_API MATCHES "OpenGL")
  message(STATUS "Looking for OpenGL dependencies")
  set(OpenGL_GL_PREFERENCE "GLVND")
  find_package(OpenGL REQUIRED)
  find_package(GLEW REQUIRED)
  # include directories
  include_directories(${GLEW_INCLUDE_DIRS})
  list(APPEND PCV_DEPS GLEW::GLEW ${OPENGL_LIBRARIES})
endif(RENDER_API MATCHES "OpenGL")

set(PCV_SRC "${PCV_CORE}/src")
set(PCV_SRCS "${PCV_SRC}/utils/windows.cpp")

# for testing purposes only
add_executable(lib lib.cpp utils/windows.cpp)
target_link_libraries(lib glfw)

add_library(pcv STATIC ${PCV_SRCS})
target_link_libraries(
  pcv
  PRIVATE stdc++fs
  PUBLIC ${PCV_DEPS})
target_include_directories(pcv INTERFACE "${PCV_CORE}/include")
