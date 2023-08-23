#pragma once

#include <cstdint>
#include <map>
#include <src/mos6502/operation.h>

namespace mos6502 {
  class Instruction;
  class AddressMode;
  class CPU;

  using GroupMapping = std::map<  // MAPPING OF
    uint8_t,                      // Lowest 2 bits OF OPCODE maps
    std::pair<                    //   to a PAIR CONTAINING
      std::map<                   //     a MAP of
        uint8_t,                  //       Highest 3 bits of OPCODE mapping to
        const Instruction &       //         the Instruction
        >,                        //     and
      std::map<                   //     a map of
        uint8_t,                  //       Middle 3 bits of OPCODE mapping to
        const AddressMode &       //         the Address mode
        >>>;

  class OpCodeTable
  {
  public:
    Operation lookup(uint8_t opcode);

  private:
    Operation lookupWithParser(uint8_t opcode);

  private:
    static const GroupMapping mapping;
  };
}// namespace mos6502
