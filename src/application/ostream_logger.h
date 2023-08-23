#pragma once

#include <ostream>
#include <src/interface/logger.h>

namespace application {
  class OStreamLogger : public emulator::Logger
  {
  public:
    OStreamLogger(std::ostream &out);
    void log(std::string_view message);

  private:
    std::ostream &out_;
  };
} // namespace application
