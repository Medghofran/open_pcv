#pragma once

#include <ostream>
#include <chrono>
#include <string>

namespace opcv::utils {

template<typename units, char const *unitname>
struct timer {
private:
  std::chrono::high_resolution_clock::time_point startPoint_;
  std::string message_;
  std::ostream &ostream_;

public:
  template<typename istring>
  timer(const istring &message, std::ostream &stream) : message_(std::move(message)), startPoint_(std::chrono::high_resolution_clock::now()), ostream_(stream) {
  }

  ~timer() {
    auto current = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<units>(current - startPoint_);

    ostream_ << message_ << std::to_string(elapsed.count()) << " (" << unitname << ")\n";
  }
};

constexpr char __micros[] = "micros";
constexpr char __millis[] = "millis";
constexpr char __nanos[] = "nanos";


using microtimer = timer<std::chrono::microseconds, __micros>;
using millitimer = timer<std::chrono::milliseconds, __millis>;
using nanotimer = timer<std::chrono::nanoseconds, __nanos>;

}// namespace opcv::utils