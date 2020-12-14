#pragma once

#include <cstdint>
#include <functional>
#include <string>
#include <any>
#include <vector>
#include <memory>
#include "events.hpp"

namespace opcv::utils {

enum class windowState : int8_t {
  ERROR = -1,
  UNSET = 0,
  INITIALIZED = 1,
  LOOPING = 2,
  CLOSED = 3
};

class window {
private:
  windowState state_;
  uint16_t height_, width_;
  std::string title_;
  std::any nativeHandler_;

  // event delegates
  delegate(void, newFrameEvent, (), ());
  delegate(void, createEvent, (), ());
  delegate(void, terminateEvent, (), ());

  // window manager as friend class
  friend class window_handler;

public:
  // public events
  event(newFrameEvent, onNewFrame);
  event(createEvent, onCreate);
  event(terminateEvent, onTerminate);

  // instance methods
  template<typename istring>
  window(uint16_t height, uint16_t width, const istring &title = "") : state_(windowState::UNSET), height_(height), width_(width), title_(std::move(title)) {
    onCreate.invoke();
  }

  ~window() {
    onTerminate.invoke();
  }

  inline windowState state() { return state_; }
  inline auto getSize() { return std::make_pair(height_, width_); }
};

class window_handler {
private:
  std::vector<window> windows_;
  static std::unique_ptr<window_handler> handler;

private:
  window_handler();
  friend std::unique_ptr<window_handler> std::make_unique<window_handler>();

public:
  ~window_handler();
  static inline const window_handler &getInstance() {
    if (!handler.get()) {
      handler = std::make_unique<window_handler>();
    }

    //return const ref of the singleton object
    return *handler.get();
  }

  window &createWindow(uint16_t height, uint16_t width, const std::string &title);

  void closeWindow(window &);
  void closeAllWindows();

  void show(window &);
  void hide(window &);
};

}// namespace opcv::utils
