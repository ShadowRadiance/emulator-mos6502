#include "operation.h"

#include <src/mos6502/address_mode.h>
#include <src/mos6502/instruction.h>

namespace mos6502 {

  Operation::Operation(const Instruction &instruction, const AddressMode &addressMode)
          : instruction_(instruction)
          , addressMode_(addressMode) {}

  void Operation::execute(mos6502::CPU &cpu) const {
    instruction_.execute(addressMode_, cpu);
  }

}// namespace mos6502
