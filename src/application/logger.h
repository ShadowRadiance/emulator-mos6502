#pragma once

#include <ostream>
#include <string_view>

namespace application {
  class Logger
  {
  public:
    Logger(std::ostream &out);
    void log(std::string_view message);

  private:
    std::ostream &out_;
  };
} // namespace application
