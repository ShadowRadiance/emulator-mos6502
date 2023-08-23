#include "nop.h"

#include <format>
#include <src/mos6502/addressing/modes.h>
#include <typeinfo>

namespace mos6502 {
  namespace operations {
    NOP::NOP(mos6502::CPU &cpu, emulator::Logger &logger) : Base(cpu, logger, "i") {}

    std::string NOP::name() const {
      return "NOP";
    }
    void NOP::execute() {
      logger().log(std::format("{} {}", name(), mode()));
      return;
    }
  } // namespace operations

} // namespace mos6502
