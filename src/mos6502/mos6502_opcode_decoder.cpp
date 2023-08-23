#include <format>
#include <map>
#include <src/mos6502/cpu.h>
#include <stdexcept>
#include <string>
#include <vector>

namespace mos6502 {
  CPU::Operation CPU::decode(uint8_t opcode) {
    switch (opcode) {
    case 0x00: return {"BRK", "i"};
    case 0x08: return {"PHP", "i"};
    case 0x10: return {"BPL", "r"};
    case 0x24: return {"BIT", "zp"};
    case 0xEA: return {"NOP", "i"};
    default: return lookup_by_parser(opcode);
    }
  }

  struct OpCodeParser
  {
    OpCodeParser(uint8_t opcode) { code = opcode; }

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

  const std::map<uint8_t, std::string> parsedInstructions = {};

  using InstTable = std::map<uint8_t, std::string>;
  using ModeTable = std::map<uint8_t, std::string>;

  InstTable instTable00{
    {0b001, "BIT"},
    {0b100, "STY"},
    {0b101, "LDY"},
    {0b110, "CPY"},
    {0b111, "CPX"},
  };

  ModeTable modeTable00{
    {0b000, "#"},
    {0b001, "zp"},
    {0b011, "a"},
    {0b101, "zp,x"},
    {0b111, "a,x"},
  };

  InstTable instTable01{
    {0b000, "ORA"},
    {0b001, "AND"},
    {0b010, "EOR"},
    {0b011, "ADC"},
    {0b100, "STA"},
    {0b101, "LDA"},
    {0b110, "CMP"},
    {0b111, "SBC"},
  };

  ModeTable modeTable01{
    {0b000, "(zp,x)"},
    {0b001, "zp"},
    {0b010, "#"},
    {0b011, "a"},
    {0b100, "(zp),y"},
    {0b101, "zp,x"},
    {0b110, "a,y"},
    {0b111, "a,x"},
  };

  InstTable instTable10{
    {0b000, "ASL"},
    {0b001, "ROL"},
    {0b010, "LSR"},
    {0b011, "ROR"},
    {0b100, "STX"},
    {0b101, "LDX"},
    {0b110, "DEC"},
    {0b111, "INC"},
  };

  ModeTable modeTable10{
    {0b000, "#"},
    {0b001, "zp"},
    {0b010, "A"},
    {0b011, "a"},
    {0b101, "zp,x"},
    {0b111, "a,x"},
  };

  using Group = std::pair<InstTable, ModeTable>;
  using GroupMapping = std::map<uint8_t, Group>;

  GroupMapping mapping{
    {0b00, {instTable00, modeTable00}},
    {0b01, {instTable01, modeTable01}},
    {0b10, {instTable10, modeTable10}},
  };

  CPU::Operation CPU::lookup_by_parser(uint8_t opcode) {
    OpCodeParser parser{opcode};

    Group tablesPair = mapping.at(parser.suffix);

    InstTable instTable = tablesPair.first;
    auto instructionIt = instTable.find(parser.prefix);
    if (instructionIt == instTable.end()) {
      throw std::invalid_argument(std::format("Invalid Opcode ${:02x}", opcode));
    }

    ModeTable modeTable = tablesPair.second;
    auto addressModeIt = modeTable.find(parser.mode);
    if (addressModeIt == modeTable.end()) {
      throw std::invalid_argument(std::format("Invalid Opcode ${:02x}", opcode));
    }

    std::string inst = instructionIt->second;
    std::string mode = addressModeIt->second;

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
      throw std::invalid_argument(std::format("Invalid Opcode ${:02x} ({} #)", opcode, inst));
    }
    case 0b100'010'10: /* $8A STX A */
    case 0b101'010'10: /* $AA LDX A */
    case 0b110'010'10: /* $CA DEC A */
    case 0b111'010'10: /* $EA INC A */ {
      throw std::invalid_argument(std::format("Invalid Opcode ${:02x} ({} A)", opcode, inst));
    }
    case 0b100'111'10: /* $9E STX a,x */ {
      throw std::invalid_argument(std::format("Invalid Opcode ${:02x} (STX a,x)", opcode));
    }
    case 0b001'000'00: /* $20 BIT # */
    case 0b100'000'00: /* $80 STY # */ {
      throw std::invalid_argument(std::format("Invalid Opcode ${:02x} ({} #)", opcode, inst));
    }
    case 0b001'101'00: /* $34 BIT zp,x */
    case 0b110'101'00: /* $D4 CPY zp,x */
    case 0b111'101'00: /* $F4 CPX zp,x */ {
      throw std::invalid_argument(std::format("Invalid Opcode ${:02x} ({} zp,x)", opcode, inst));
    }
    case 0b001'111'00: /* $3C BIT a,x */
    case 0b100'111'00: /* $9C STY a,x */
    case 0b110'111'00: /* $DC CPY a,x */
    case 0b111'111'00: /* $FC CPX a,x */ {
      throw std::invalid_argument(std::format("Invalid Opcode ${:02x} ({} a,x)", opcode, inst));
    }
    }

    if (parser.suffix == 0b10) {
      if (mode == "zp,x" && (inst == "STX" || inst == "LDX")) {
        return {inst, "zp,y"};
      }
      if (mode == "a,x" && inst == "LDX") {
        return {inst, "a,y"};
      }
    }

    return {inst, mode};
  }

}// namespace mos6502
