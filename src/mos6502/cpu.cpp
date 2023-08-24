#include "cpu.h"

#include <format>
#include <src/mos6502/instruction.h>

namespace mos6502 {
  const uint16_t NMIVector = 0xFFFA;    // - 0xFFFB
  const uint16_t ResetVector = 0xFFFC;  // - 0xFFFD
  const uint16_t IRQVector = 0xFFFE;    // - 0xFFFF

  CPU::CPU(application::RAM &mem, application::Logger &logger) : mem_(mem), logger_(logger) {
    reset();
  }

  void CPU::reset() {
    a = x = y = 0;
    s = 0xFF;
    pc = read_word(ResetVector);
    p = 0b00100000;
  }

  bool CPU::tick() {
    uint8_t opcode = fetch_pc_byte();
    Operation operation = opcode_table_.lookup(opcode);
    bool gotBRK = operation.instruction_ == Instruction::BRK;
    if (!gotBRK) {
      operation.execute(*this);
    } else {
      logger_.log("  END PROGRAM");
    }
    logger_.log(std::format("  Cycles: {0}", cycles));
    logger_.log(std::format("  State: A:{:02x} X:{:02x} Y:{:02x} SP:{:02x} PC:{:04x} P:{:08b}", a, x, y, s, pc, p));

    return !gotBRK;
  }

  application::Logger &CPU::logger() const {
    return logger_;
  }

  application::RAM &CPU::memory() const {
    return mem_;
  }

  uint8_t CPU::fetch_pc_byte() {
    uint8_t byte = read_byte(pc);
    increment_pc();
    return byte;
  }

  uint16_t CPU::fetch_pc_word() {
    uint16_t word = read_word(pc);
    increment_pc(2);
    return word;
  }

  void CPU::increment_pc(uint8_t n) {
    cycles++;
    pc += n;
    logger_.log(std::format("1: INCR PC to ${:04x}", pc));
  }

  uint8_t CPU::read_byte(uint16_t address) {
    cycles++;
    uint8_t byte = mem_[address];
    logger_.log(std::format("1: READ ${:04x} => ${:02x}", address, byte));
    return mem_[address];
  }

  void CPU::write_byte(uint16_t address, uint8_t byte) {
    cycles++;
    mem_[address] = byte;
    logger_.log(std::format("1: WRITE ${:02x} to ${:04x}", byte, address));
  }

  uint16_t CPU::read_word(uint16_t address) {
    uint16_t lo_byte = read_byte(address);
    uint16_t hi_byte = read_byte(address + 1);
#if LITTLE_ENDIAN
    return lo_byte | hi_byte << 8;
#else
    return hi_byte | lo_byte << 8;
#endif
  }

  void CPU::write_word(uint16_t address, uint16_t word) {
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
