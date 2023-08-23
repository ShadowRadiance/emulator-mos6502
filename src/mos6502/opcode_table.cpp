#include "opcode_table.h"

#include <format>
#include <src/mos6502/address_mode.h>
#include <src/mos6502/instruction.h>
#include <stdexcept>

namespace mos6502 {

  struct ParsedOpCode
  {
    ParsedOpCode(uint8_t opcode) { code = opcode; }

    union
    {
      uint8_t code;
      struct
      {
        uint8_t suffix :2; // bits 0, 1
        uint8_t mode   :3; // bits 2,3,4
        uint8_t prefix :3; // bits 5,6,7
      };
    };
  };

  Operation OpCodeTable::lookup(uint8_t opcode) {
    switch (opcode) {
    case 0x00: return {Instruction::BRK, AddressMode::Implied};
    case 0x08: return {Instruction::PHP, AddressMode::Implied};
    case 0x10: return {Instruction::BPL, AddressMode::Relative};
    case 0x24: return {Instruction::BIT, AddressMode::ZeroPage};
    case 0xEA: return {Instruction::NOP, AddressMode::Implied};
    default: return lookupWithParser(opcode);
    }
  }

  Operation OpCodeTable::lookupWithParser(uint8_t opcode) {
    ParsedOpCode parsedOpcode{opcode};

    auto tablesPair = mapping.at(parsedOpcode.suffix);
    auto instTable = tablesPair.first;
    auto instructionIt = instTable.find(parsedOpcode.prefix);
    if (instructionIt == instTable.end()) {
      throw std::invalid_argument(std::format("Invalid Opcode ${:02x}", opcode));
    }

    auto modeTable = tablesPair.second;
    auto addressModeIt = modeTable.find(parsedOpcode.mode);
    if (addressModeIt == modeTable.end()) {
      throw std::invalid_argument(std::format("Invalid Opcode ${:02x}", opcode));
    }

    const Instruction &inst = instructionIt->second;
    const AddressMode &mode = addressModeIt->second;

    // handle the weirdness

    switch (opcode) {
    case 0b100'010'01: /* $89 STA # */ {
      throw std::invalid_argument(std::format("Invalid Opcode ${:02x} (STA #)", opcode));
    }
    case 0b000'000'10: /* $02 ASL # */
    case 0b001'000'10: /* $22 ROL # */
    case 0b010'000'10: /* $42 LSR # */
    case 0b011'000'10: /* $62 ROR # */
    case 0b100'000'10: /* $82 STX # */
    case 0b110'000'10: /* $C2 DEC # */
    case 0b111'000'10: /* $E2 INC # */ {
      throw std::invalid_argument(std::format("Invalid Opcode ${:02x} ({} #)", opcode, inst.name()));
    }
    case 0b100'010'10: /* $8A STX A */
    case 0b101'010'10: /* $AA LDX A */
    case 0b110'010'10: /* $CA DEC A */
    case 0b111'010'10: /* $EA INC A */ {
      throw std::invalid_argument(std::format("Invalid Opcode ${:02x} ({} A)", opcode, inst.name()));
    }
    case 0b100'111'10: /* $9E STX a,x */ {
      throw std::invalid_argument(std::format("Invalid Opcode ${:02x} (STX a,x)", opcode));
    }
    case 0b001'000'00: /* $20 BIT # */
    case 0b100'000'00: /* $80 STY # */ {
      throw std::invalid_argument(std::format("Invalid Opcode ${:02x} ({} #)", opcode, inst.name()));
    }
    case 0b001'101'00: /* $34 BIT zp,x */
    case 0b110'101'00: /* $D4 CPY zp,x */
    case 0b111'101'00: /* $F4 CPX zp,x */ {
      throw std::invalid_argument(std::format("Invalid Opcode ${:02x} ({} zp,x)", opcode, inst.name()));
    }
    case 0b001'111'00: /* $3C BIT a,x */
    case 0b100'111'00: /* $9C STY a,x */
    case 0b110'111'00: /* $DC CPY a,x */
    case 0b111'111'00: /* $FC CPX a,x */ {
      throw std::invalid_argument(std::format("Invalid Opcode ${:02x} ({} a,x)", opcode, inst.name()));
    }
    }

    if (parsedOpcode.suffix == 0b10) {
      if (mode == AddressMode::ZeroPageX && (inst == Instruction::STX || inst == Instruction::LDX)) {
        return {inst, AddressMode::ZeroPageY};
      }
      if (mode == AddressMode::AbsoluteX && inst == Instruction::LDX) {
        return {inst, AddressMode::AbsoluteY};
      }
    }

    return {inst, mode};
  }

  const GroupMapping OpCodeTable::mapping{
    {0b00,
     {{
        {0b001, Instruction::BIT},
        {0b100, Instruction::STY},
        {0b101, Instruction::LDY},
        {0b110, Instruction::CPY},
        {0b111, Instruction::CPX},
      },
      {
        {0b000, AddressMode::Immediate},
        {0b001, AddressMode::ZeroPage},
        {0b011, AddressMode::Absolute},
        {0b101, AddressMode::ZeroPageX},
        {0b111, AddressMode::AbsoluteX},
      }}},
    {0b01,
     {{
        {0b000, Instruction::ORA},
        {0b001, Instruction::AND},
        {0b010, Instruction::EOR},
        {0b011, Instruction::ADC},
        {0b100, Instruction::STA},
        {0b101, Instruction::LDA},
        {0b110, Instruction::CMP},
        {0b111, Instruction::SBC},
      },
      {
        {0b000, AddressMode::ZeroPageXIndirect},
        {0b001, AddressMode::ZeroPage},
        {0b010, AddressMode::Immediate},
        {0b011, AddressMode::Absolute},
        {0b100, AddressMode::ZeroPageIndirectY},
        {0b101, AddressMode::ZeroPageX},
        {0b110, AddressMode::AbsoluteY},
        {0b111, AddressMode::AbsoluteX},
      }}},
    {0b10,
     {{
        {0b000, Instruction::ASL},
        {0b001, Instruction::ROL},
        {0b010, Instruction::LSR},
        {0b011, Instruction::ROR},
        {0b100, Instruction::STX},
        {0b101, Instruction::LDX},
        {0b110, Instruction::DEC},
        {0b111, Instruction::INC},
      },
      {
        {0b000, AddressMode::Immediate},
        {0b001, AddressMode::ZeroPage},
        {0b010, AddressMode::Accumulator},
        {0b011, AddressMode::Absolute},
        {0b101, AddressMode::ZeroPageX},
        {0b111, AddressMode::AbsoluteX},
      }}},
  };

}// namespace mos6502
