#pragma once

#include <functional>
#include <queue>
#include <utility>
#include <vector>

namespace opcv::utils {

#define delegate(RET_TYPE, DELEGATE, PARAMS, PARAM_NAMES)                       \
  typedef std::function<RET_TYPE PARAMS> DELEGATE;                              \
  class Event##DELEGATE {                                                       \
  private:                                                                      \
    std::vector<DELEGATE> delegates_;                                           \
    bool isReoccurring_ = true;                                                 \
                                                                                \
  public:                                                                       \
    Event##DELEGATE(bool isReoccuring = true) : isReoccurring_(isReoccuring) {} \
                                                                                \
    Event##DELEGATE &operator+=(DELEGATE func) {                                \
      delegates_.push_back(func);                                               \
      return *this;                                                             \
    }                                                                           \
    void clear() { delegates_.clear(); }                                        \
    void invoke PARAMS {                                                        \
      for (auto it : delegates_) {                                              \
        it PARAM_NAMES;                                                         \
      }                                                                         \
    }                                                                           \
  };
#define event(DELEGATE, EVENT_NAME) Event##DELEGATE EVENT_NAME;

}// namespace opcv::utils