#include <iostream>
#include <opcv/utils/window_handler.hpp>
#include <opcv/utils/logger.hpp>

int main() {
  // create a logger instance
  opcv::utils::logger logger(std::cout);

  // get window handler singleton instance
  auto instance = opcv::utils::window_handler::getInstance();

  // create a new window
  auto win = instance.createWindow(600, 800, "penis brain");
  // hook up a custom payload to the new frame event
  win.onNewFrame += [=]() { logger.logInfo("New frame event invoked"); };

  //show window
  instance.show(win);

  // close window
  instance.closeWindow(win);

  return 0;
}