#pragma once

#include <ostream>
#include <string>
#include <typeinfo>

namespace opcv::utils {

/* console colors */
struct ccolors {
  static constexpr const char *reset = "\033[0m";
  static constexpr const char *red = "\033[031m";
  static constexpr const char *green = "\033[032m";
  static constexpr const char *yellow = "\033[033m";
  static constexpr const char *blue = "\033[034m";
  static constexpr const char *magenta = "\033[035m";
  static constexpr const char *cyan = "\033[036m";
  static constexpr const char *white = "\033[037m";
};

struct logger {
private:
  std::ostream &ostream_;

public:
  logger(std::ostream &ostream) : ostream_(ostream) {}
  ~logger() = default;

  template<typename istring>
  void logInfo(const istring &message) const {
    ostream_ << ccolors::green << "INFO:: " << ccolors::reset << message << "\n";
  }

  template<typename entity, typename istring>
  void logInfo(const istring &message) const {
    ostream_ << ccolors::green << "INFO::" << ccolors::magenta << "[" << typeid(entity).name() << "]" << ccolors::reset << message << "\n";
  }

  template<typename istring>
  void logWarning(const istring &message) const {
    ostream_ << ccolors::yellow << "INFO:: " << ccolors::reset << message << "\n";
  }

  template<typename entity, typename istring>
  void logWarning(const istring &message) const {
    ostream_ << ccolors::yellow << "INFO::" << ccolors::magenta << "[" << typeid(entity).name() << "]" << ccolors::reset << message << "\n";
  }

  template<typename istring>
  void logError(const istring &message) const {
    ostream_ << ccolors::red << "INFO:: " << ccolors::reset << message << "\n";
  }

  template<typename entity, typename istring>
  void logError(const istring &message) const {
    ostream_ << ccolors::red << "INFO::" << ccolors::magenta << "[" << typeid(entity).name() << "]" << ccolors::reset << message << "\n";
  }
};

}// namespace opcv::utils
