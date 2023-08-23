#include "and.h"

#include <format>
#include <src/mos6502/addressing/modes.h>
#include <typeinfo>

namespace mos6502 {
  namespace operations {
    AND::AND(mos6502::CPU &cpu, emulator::Logger &logger, std::string mode) : Base(cpu, logger, mode) {}

    std::string AND::name() const {
      return "AND";
    }
    void AND::execute() {
      logger().log(std::format("{} {}", name(), mode()));
      return;
    }
  } // namespace operations

} // namespace mos6502
