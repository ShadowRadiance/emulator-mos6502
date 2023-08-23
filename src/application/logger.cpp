#include "logger.h"

namespace application {
  Logger::Logger(std::ostream &out) : out_(out) {}

  void Logger::log(std::string_view message) {
    out_ << message << "\n";
  }
} // namespace application
