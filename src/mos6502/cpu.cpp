#include "./cpu.h"

#include <format>

namespace mos6502 {
  CPU::CPU(RandomAccessMemory &ram, Logger &logger) : ram_(ram), logger_(logger) {
    reset();
  }

  void CPU::reset() {
    a = x = y = 0;
    s = 0xFF;
    pc = 0;
    p = 0b00100000;
  }

  bool CPU::tick() {
    uint8_t opcode = fetch_pc_byte();
    std::unique_ptr<Operation> operation = decode(opcode);

    operation->execute();

    if (cycles > 10) {
      return false;
    }

    logger_.log(std::format("Cycles {0}", cycles));

    return true;
  }

  uint8_t CPU::fetch_pc_byte() {
    uint8_t byte = read_byte(pc);
    logger_.log(std::format("FETCHED {0} from {1}", byte, pc));
    increment_pc();
    return byte;
  }

  uint16_t CPU::fetch_pc_word() {
    uint16_t word = read_word(pc);
    logger_.log(std::format("FETCHED {0} from {1}", word, pc));
    increment_pc(2);
    return word;
  }

  void CPU::increment_pc(uint8_t n) {
    cycles++;
    pc += n;
    logger_.log(std::format("INCR PC to {0} (1c)", pc));
  }

  uint8_t CPU::read_byte(uint16_t address) {
    cycles++;
    uint8_t byte = ram_[address];
    logger_.log(std::format("READ {0} from {1} (1c)", byte, address));
    return ram_[address];
  }

  void CPU::write_byte(uint16_t address, uint8_t byte) {
    cycles++;
    ram_[address] = byte;
    logger_.log(std::format("WROTE {0} from {1} (1c)", byte, address));
  }

  uint16_t CPU::read_word(uint16_t address) {
    logger_.log(std::format("READING WORD from {0}", address));

    uint16_t lo_byte = read_byte(address);
    uint16_t hi_byte = read_byte(address + 1);
#if LITTLE_ENDIAN
    return lo_byte | hi_byte << 8;
#else
    return hi_byte | lo_byte << 8;
#endif
  }

  void CPU::write_word(uint16_t address, uint16_t word) {
    logger_.log(std::format("WRITING WORD to {0}", address));
#if LITTLE_ENDIAN
    uint8_t lo_byte = word & 0xFF;
    uint8_t hi_byte = (word >> 8) & 0xFF;
#else
    uint8_t lo_byte = (word >> 8) & 0xFF;
    uint8_t hi_byte = word & 0xFF;
#endif
    write_byte(address, lo_byte);
    write_byte(address + 1, hi_byte);
  }

  std::map<std::string, std::unique_ptr<AddressMode>> init() {
    std::map<std::string, std::unique_ptr<AddressMode>> map;

    map["(a)"] = std::make_unique<addressing::AbsoluteIndirect>();
    map["a,x"] = std::make_unique<addressing::AbsoluteX>();
    map["a,y"] = std::make_unique<addressing::AbsoluteY>();
    map["a"] = std::make_unique<addressing::Absolute>();
    map["A"] = std::make_unique<addressing::Accumulator>();
    map["#"] = std::make_unique<addressing::Immediate>();
    map["i"] = std::make_unique<addressing::Implied>();
    map["r"] = std::make_unique<addressing::Relative>();
    map["(zp),y"] = std::make_unique<addressing::ZeroPageIndirectY>();
    map["(zp,x)"] = std::make_unique<addressing::ZeroPageXIndirect>();
    map["zp,x"] = std::make_unique<addressing::ZeroPageX>();
    map["zp,y"] = std::make_unique<addressing::ZeroPageY>();
    map["zp"] = std::make_unique<addressing::ZeroPage>();

    return map;
  }

  std::map<std::string, std::unique_ptr<AddressMode>> CPU::addressModes = init();

}// namespace mos6502

// a single INSTRUCTION takes multiple cycles
// INC_PC: 1 cycle
// FETCH: 1 cycle -> fetch opcode at current PC (into IR)
// DECODE: 1 cycle -> determine instruction and addressing mode
// EXECUTE: multiple cycles
//  --> (maybe) read additional data from PC+1, PC+2...
//  --> perform instruction

// EXAMPLE `STY $03`:
// FETCH: Read PC: $84
// DECODE: $84 means STY zp
// EXECUTE:
//  --> read PC+1: $A2
//  --> store the value in Y in memory location $00A2

// EXAMPLE `LDY $03`:
// FETCH: Read PC: $xx
// DECODE: $xx means LDY zp
// EXECUTE:
//  --> read PC+1: $A2
//  --> store the value in memory location $00A2 to Y