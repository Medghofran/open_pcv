#include <GLFW/glfw3.h>
#include <opcv/utils/window_handler.hpp>
#include <opcv/utils/logger.hpp>
#include <iostream>
#include <cassert>

/**
 * create windows using the GLFW API
*/


namespace opcv::utils {

std::unique_ptr<window_handler> window_handler::handler;

window_handler::window_handler() {
  auto initResult = glfwInit();
  if (!initResult) {
    logger(std::cout).logError("error initiating glfw");
  }
  assert(initResult && "error initiating glfw");
}

window_handler::~window_handler() {
  glfwTerminate();
}

window &window_handler::createWindow(uint16_t height, uint16_t width, const std::string &title) {
  // create window instance and then try to assign it's native pointer to the GLFWWindow pointer
  window win(height, width, title);
  // create window
  win.nativeHandler_ = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

  // assertions
  if (std::any_cast<GLFWwindow *>(win.nativeHandler_) == nullptr) {
    logger(std::cout).logError("error creating glfw window");
    win.state_ = windowState::ERROR;
  }
  assert(std::any_cast<GLFWwindow *>(win.nativeHandler_) != nullptr && "error creating glfw window");

  win.state_ = windowState::INITIALIZED;

  // make current window context as the current.
  glfwMakeContextCurrent(std::any_cast<GLFWwindow *>(win.nativeHandler_));

  // add window to the saved windows
  windows_.emplace_back(win);

  return windows_.back();
}

void window_handler::closeWindow(window &win) {
  // terminate glfw native pointer
  glfwSetWindowShouldClose(std::any_cast<GLFWwindow *>(win.nativeHandler_), true);
  win.state_ = windowState::CLOSED;
  win.nativeHandler_ = nullptr;
}


void window_handler::closeAllWindows() {
  while (!windows_.empty()) {
    auto window = windows_.back();
    closeWindow(window);
    windows_.pop_back();
  }
}

}// namespace opcv::utils