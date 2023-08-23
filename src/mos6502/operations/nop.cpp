#include "./nop.h"

#include <src/components/address_modes.h>
#include <src/components/mos6502.h>
#include <typeinfo>

namespace components {
  namespace operations {
    NOP::NOP(CPU &cpu, Logger &logger) : Base(cpu, logger, *MOS6502::addressModes["i"]) {}

    void NOP::execute() {
      logger().log(name());
      return;
    }
  } // namespace operations

} // namespace components
