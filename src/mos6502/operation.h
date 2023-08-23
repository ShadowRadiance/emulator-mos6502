#pragma once

#include <string>

namespace mos6502 {
  class AddressMode;
  class CPU;
  class Instruction;

  class Operation
  {
  public:
    Operation(const Instruction &instruction, const AddressMode &addressMode);
    void execute(mos6502::CPU &cpu) const;

  private:
    const Instruction &instruction_;
    const AddressMode &addressMode_;
  };

}// namespace mos6502
