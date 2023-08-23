#include "brk.h"

#include <format>
#include <src/mos6502/addressing/modes.h>
#include <src/mos6502/cpu.h>
#include <typeinfo>

namespace mos6502 {
  namespace operations {
    BRK::BRK(mos6502::CPU &cpu, emulator::Logger &logger) : Base(cpu, logger, "i") {}

    std::string BRK::name() const {
      return "BRK";
    }
    void BRK::execute() {
      logger().log(std::format("{} {}", name(), mode()));
      return;
    }
  } // namespace operations

} // namespace mos6502
