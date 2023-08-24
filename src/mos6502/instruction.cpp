#include "instruction.h"

#include <format>
#include <src/mos6502/address_mode.h>
#include <src/mos6502/cpu.h>
#include <stdexcept>

namespace mos6502 {
  const uint16_t StackBase = 0x0100;

  uint8_t bitN(uint16_t value, uint8_t n) {
    return (value & uint16_t(1 << n)) >> n;
  }

  Instruction::Instruction(std::string_view name, MemFn memfn) : name_(name), memfn_(memfn) {}

  std::string_view Instruction::name() const {
    return name_;
  }

  bool Instruction::operator==(const Instruction &other) const {
    return &other == this;
  }

  void Instruction::execute(const AddressMode &addressMode, CPU &cpu) const {
    cpu.logger().log(std::format("RESOLVED {} {}", name(), addressMode.code()));
    (this->*memfn_)(addressMode, cpu);
  }

  void Instruction::set_a(CPU &cpu, uint8_t value) const {
    cpu.a = value;
    set_n(cpu, value);
    set_z(cpu, value);
  }
  void Instruction::set_x(CPU &cpu, uint8_t value) const {
    cpu.x = value;
    set_n(cpu, value);
    set_z(cpu, value);
  }
  void Instruction::set_y(CPU &cpu, uint8_t value) const {
    cpu.y = value;
    set_n(cpu, value);
    set_z(cpu, value);
  }

  void Instruction::set_c(CPU &cpu, uint16_t value_with_carry) const {
    cpu.c = bitN(value_with_carry, 8);
  }
  void Instruction::set_n(CPU &cpu, uint8_t value) const {
    cpu.n = bitN(value, 7);
  }
  void Instruction::set_v(CPU &cpu, uint8_t value, uint8_t op1, uint8_t op2) const {
    uint8_t op1sgn = bitN(op1, 7);
    uint8_t op2sgn = bitN(op2, 7);
    uint8_t valsgn = bitN(value, 7);
    cpu.v = ((op1sgn ^ ~op2sgn) & valsgn);
  }
  void Instruction::set_z(CPU &cpu, uint8_t value) const {
    cpu.z = value == 0;
  }

  void Instruction::branch(const AddressMode &mode, CPU &cpu) const {
    int8_t offset = (int8_t)mode.value(cpu);
    uint16_t address = cpu.pc + offset;
    cpu.pc = address;
  }

#pragma region LOAD, STORE, TRANSFER
  void Instruction::Lda(const AddressMode &mode, CPU &cpu) const {
    // Load Value to A
    uint8_t value = mode.value(cpu);
    set_a(cpu, value);
    cpu.logger().log(std::format("--{} WROTE ${:02x} to A register", name(), value));
  }
  void Instruction::Ldx(const AddressMode &mode, CPU &cpu) const {
    // Load Value to X
    uint8_t value = mode.value(cpu);
    set_x(cpu, value);
    cpu.logger().log(std::format("--{} WROTE ${:02x} to X register", name(), value));
  }
  void Instruction::Ldy(const AddressMode &mode, CPU &cpu) const {
    // Load Value to Y
    uint8_t value = mode.value(cpu);
    set_y(cpu, value);
    cpu.logger().log(std::format("--{} WROTE ${:02x} to Y register", name(), value));
  }
  void Instruction::Sta(const AddressMode &mode, CPU &cpu) const {
    // Store A to Address
    uint16_t address = mode.address(cpu);
    uint8_t value = cpu.a;
    cpu.write_byte(address, value);
    cpu.logger().log(std::format("--{} WROTE A(${:02x}) to ${:04x}", name(), value, address));
  }
  void Instruction::Stx(const AddressMode &mode, CPU &cpu) const {
    // Store X to Address
    uint16_t address = mode.address(cpu);
    uint8_t value = cpu.x;
    cpu.write_byte(address, value);
    cpu.logger().log(std::format("--{} WROTE X(${:02x}) to ${:04x}", name(), value, address));
  }
  void Instruction::Sty(const AddressMode &mode, CPU &cpu) const {
    // Store Y to Address
    uint16_t address = mode.address(cpu);
    uint8_t value = cpu.y;
    cpu.write_byte(address, value);
    cpu.logger().log(std::format("--{} WROTE Y(${:02x}) to ${:04x}", name(), value, address));
  }
  void Instruction::Tax(const AddressMode &mode, CPU &cpu) const {
    // Transfer A to X
    uint8_t value = cpu.a;
    set_x(cpu, value);
    cpu.logger().log(std::format("--{} WROTE A(${:02x}) to X", name(), value));
  }
  void Instruction::Tay(const AddressMode &mode, CPU &cpu) const {
    // Transfer A to Y
    uint8_t value = cpu.a;
    set_y(cpu, value);
    cpu.logger().log(std::format("--{} WROTE A(${:02x}) to Y", name(), value));
  }
  void Instruction::Tsx(const AddressMode &mode, CPU &cpu) const {
    // Transfer S to X
    uint8_t value = cpu.s;
    set_x(cpu, value);
    cpu.logger().log(std::format("--{} WROTE S(${:02x}) to X", name(), value));
  }
  void Instruction::Txa(const AddressMode &mode, CPU &cpu) const {
    // Transfer X to A
    uint8_t value = cpu.x;
    set_a(cpu, value);
    cpu.logger().log(std::format("--{} WROTE X(${:02x}) to A", name(), value));
  }
  void Instruction::Txs(const AddressMode &mode, CPU &cpu) const {
    // Transfer X to S
    uint8_t value = cpu.x;
    cpu.s = value;
    cpu.logger().log(std::format("--{} WROTE X(${:02x}) to S", name(), value));
  }
  void Instruction::Tya(const AddressMode &mode, CPU &cpu) const {
    // Transfer Y to A
    uint8_t value = cpu.y;
    set_a(cpu, value);
    cpu.logger().log(std::format("--{} WROTE Y(${:02x}) to A", name(), value));
  }
#pragma endregion LOAD, STORE, TRANSFER

#pragma region STACK
  /*
  The stack is a 256-byte LIFO stack, spanning $0100-$01FF.
  The stack pointer (S) starts at 0xFF.
  When a byte is pushed onto the stack it will be placed at $0100+S. Then S will be decremented.
  When a byte is popped from the stack, S will be incremented.
  */
  void Instruction::Pha(const AddressMode &mode, CPU &cpu) const {
    // Push A
    cpu.write_byte(StackBase + cpu.s, cpu.a);
    cpu.s--;
  }
  void Instruction::Php(const AddressMode &mode, CPU &cpu) const {
    // Push P (status)
    uint8_t value = cpu.p;
    value |= 0b00110000; // set bits 4 and 5
    cpu.write_byte(StackBase + cpu.s, value);
    cpu.s--;
  }
  void Instruction::Pla(const AddressMode &mode, CPU &cpu) const {
    // Pull A
    cpu.s++;
    uint8_t value = cpu.read_byte(StackBase + cpu.s);
    set_a(cpu, value);
  }
  void Instruction::Plp(const AddressMode &mode, CPU &cpu) const {
    // Pull P
    cpu.s++;
    uint8_t value = cpu.read_byte(StackBase + cpu.s);
    uint8_t existing_b = cpu.b;
    cpu.p = value;
    cpu.b = existing_b;
  }
#pragma endregion STACK

#pragma region INCREMENT, DECREMENT
  void Instruction::Dec(const AddressMode &mode, CPU &cpu) const {
    // Decrement element at address by 1
    uint16_t address = mode.address(cpu);
    uint8_t value = cpu.read_byte(address);
    value--;
    cpu.write_byte(address, value);
    set_n(cpu, value);
    set_z(cpu, value);
  }
  void Instruction::Dex(const AddressMode &mode, CPU &cpu) const {
    // Decrement X by 1
    uint8_t value = cpu.x;
    value--;
    set_x(cpu, value);
  }
  void Instruction::Dey(const AddressMode &mode, CPU &cpu) const {
    // Decrement Y by 1
    uint8_t value = cpu.y;
    value--;
    set_y(cpu, value);
  }
  void Instruction::Inc(const AddressMode &mode, CPU &cpu) const {
    // Increment element at address by 1
    uint16_t address = mode.address(cpu);
    uint8_t value = cpu.read_byte(address);
    value++;
    cpu.write_byte(address, value);
    set_n(cpu, value);
    set_z(cpu, value);
  }
  void Instruction::Inx(const AddressMode &mode, CPU &cpu) const {
    uint8_t value = cpu.x;
    value++;
    set_x(cpu, value);
  }
  void Instruction::Iny(const AddressMode &mode, CPU &cpu) const {
    uint8_t value = cpu.y;
    value++;
    set_y(cpu, value);
  }
#pragma endregion INCREMENT, DECREMENT

#pragma region ARITHMETIC
  void Instruction::Adc(const AddressMode &mode, CPU &cpu) const {
    if (cpu.d == 1) {
      throw std::logic_error("We haven't implemented BCD mode");
    }

    // Add (mem) to A with Carry (prepare by CLC)
    uint8_t add = mode.value(cpu);
    uint16_t value_with_c = uint16_t(cpu.a) + uint16_t(add) + cpu.c;

    set_c(cpu, value_with_c);
    set_v(cpu, value_with_c & 0xFF, cpu.a, add);
    set_a(cpu, value_with_c & 0xFF);
  }
  void Instruction::Sbc(const AddressMode &mode, CPU &cpu) const {
    if (cpu.d == 1) {
      throw std::logic_error("We haven't implemented BCD mode");
    }

    // Subtract (mem) from A with Borrow (prepare by SEC)
    uint8_t sub = mode.value(cpu);
    uint8_t add = sub ^ 0xFF;
    // (C<<8 & A) - SUB  ===  A + (SUB XOR ff) + C
    uint16_t value_with_c = uint16_t(cpu.a) + uint16_t(add) + cpu.c;
    set_c(cpu, value_with_c);
    set_v(cpu, value_with_c & 0xFF, cpu.a, add);
    set_a(cpu, value_with_c & 0xFF);
  }
#pragma endregion ARITHMETIC

#pragma region LOGICAL
  void Instruction::And(const AddressMode &mode, CPU &cpu) const {
    // Bitwise AND with Accumulator
    uint8_t value = mode.value(cpu);
    set_a(cpu, cpu.a & value);
  }
  void Instruction::Eor(const AddressMode &mode, CPU &cpu) const {
    // Bitwise XOR with Accumulator
    uint8_t value = mode.value(cpu);
    set_a(cpu, cpu.a ^ value);
  }
  void Instruction::Ora(const AddressMode &mode, CPU &cpu) const {
    // Bitwise OR with Accumulator
    uint8_t value = mode.value(cpu);
    set_a(cpu, cpu.a | value);
  }
#pragma endregion LOGICAL

#pragma region SHIFT, ROTATE
  void Instruction::Asl(const AddressMode &mode, CPU &cpu) const {
    // 0bpqrs'tuvw,C => 0bqrst'uvw0,p
    if (mode == AddressMode::Accumulator) {
      uint8_t value = cpu.a;
      cpu.a = value << 1;
      cpu.c = bitN(value, 7);
    } else {
      uint16_t address = mode.address(cpu);
      uint8_t value = cpu.read_byte(address);
      cpu.write_byte(address, value << 1);
      cpu.c = bitN(value, 7);
    }
  }
  void Instruction::Lsr(const AddressMode &mode, CPU &cpu) const {
    // 0bpqrs'tuvw,C => 0b0pqr'stuv,w

    if (mode == AddressMode::Accumulator) {
      uint8_t value = cpu.a;
      cpu.a = value >> 1;
      cpu.c = bitN(value, 0);
    } else {
      uint16_t address = mode.address(cpu);
      uint8_t value = cpu.read_byte(address);
      cpu.write_byte(address, value >> 1);
      cpu.c = bitN(value, 0);
    }
  }
  void Instruction::Rol(const AddressMode &mode, CPU &cpu) const {
    // 0bpqrs'tuvw,C => (0bqrst'uvw0 | 0b0000'000C),p => 0bqrst'uvwC,p
    if (mode == AddressMode::Accumulator) {
      uint8_t value = cpu.a;
      cpu.a = (value << 1) | cpu.c;
      cpu.c = bitN(value, 7);
    } else {
      uint16_t address = mode.address(cpu);
      uint8_t value = cpu.read_byte(address);
      cpu.write_byte(address, (value << 1) | cpu.c);
      cpu.c = bitN(value, 7);
    }
  }
  void Instruction::Ror(const AddressMode &mode, CPU &cpu) const {
    // 0bpqrs'tuvw,C => (0b0pqr'stuv | 0bC000'0000),w => 0bCpqr'stuv,w
    if (mode == AddressMode::Accumulator) {
      uint8_t value = cpu.a;
      cpu.a = (value >> 1) | (cpu.c << 7);
      cpu.c = bitN(value, 0);
    } else {
      uint16_t address = mode.address(cpu);
      uint8_t value = cpu.read_byte(address);
      cpu.write_byte(address, (value >> 1) | (cpu.c << 7));
      cpu.c = bitN(value, 0);
    }
  }
#pragma endregion SHIFT, ROTATE

#pragma region FLAG
  void Instruction::Clc(const AddressMode &mode, CPU &cpu) const {
    cpu.c = 0;
  }
  void Instruction::Sec(const AddressMode &mode, CPU &cpu) const {
    cpu.c = 1;
  }
  void Instruction::Cld(const AddressMode &mode, CPU &cpu) const {
    cpu.d = 0;
  }
  void Instruction::Sed(const AddressMode &mode, CPU &cpu) const {
    throw std::logic_error("We haven't implemented BCD mode");
    // cpu.d = 1;
  }
  void Instruction::Cli(const AddressMode &mode, CPU &cpu) const {
    cpu.i = 0;
  }
  void Instruction::Sei(const AddressMode &mode, CPU &cpu) const {
    cpu.i = 1;
  }
  void Instruction::Clv(const AddressMode &mode, CPU &cpu) const {
    cpu.v = 0;
  }
#pragma endregion FLAG

#pragma region COMPARISON
  void Instruction::Cmp(const AddressMode &mode, CPU &cpu) const {
    // Compare with A
    uint8_t compare = cpu.a;
    uint8_t value = mode.value(cpu);

    uint8_t add = value ^ 0xFF;
    uint16_t value_with_c = uint16_t(cpu.a) + uint16_t(add);
    set_c(cpu, value_with_c);
    set_n(cpu, value_with_c & 0xFF);
    set_z(cpu, value_with_c & 0xFF);
  }
  void Instruction::Cpx(const AddressMode &mode, CPU &cpu) const {
    // Compare with X
    uint8_t compare = cpu.x;
    uint8_t value = mode.value(cpu);

    uint8_t add = value ^ 0xFF;
    uint16_t value_with_c = uint16_t(cpu.a) + uint16_t(add);
    set_c(cpu, value_with_c);
    set_n(cpu, value_with_c & 0xFF);
    set_z(cpu, value_with_c & 0xFF);
  }
  void Instruction::Cpy(const AddressMode &mode, CPU &cpu) const {
    // Compare with Y
    uint8_t compare = cpu.y;
    uint8_t value = mode.value(cpu);

    uint8_t add = value ^ 0xFF;
    uint16_t value_with_c = uint16_t(cpu.a) + uint16_t(add);
    set_c(cpu, value_with_c);
    set_n(cpu, value_with_c & 0xFF);
    set_z(cpu, value_with_c & 0xFF);
  }
#pragma endregion COMPARISON

#pragma region BRANCHING
  void Instruction::Bcc(const AddressMode &mode, CPU &cpu) const {
    // Branch on Carry Clear (all branch instructions are relative mode only)
    if (cpu.c == 0) {
      branch(mode, cpu);
    }
  }
  void Instruction::Bcs(const AddressMode &mode, CPU &cpu) const {
    // Branch on Carry Set (all branch instructions are relative mode only)
    if (cpu.c == 1) {
      branch(mode, cpu);
    }
  }
  void Instruction::Bne(const AddressMode &mode, CPU &cpu) const {
    // Branch on Not Equal (all branch instructions are relative mode only)
    if (cpu.z == 0) {
      branch(mode, cpu);
    }
  }
  void Instruction::Beq(const AddressMode &mode, CPU &cpu) const {
    // Branch on Equal (all branch instructions are relative mode only)
    if (cpu.z == 1) {
      branch(mode, cpu);
    }
  }
  void Instruction::Bpl(const AddressMode &mode, CPU &cpu) const {
    // Branch on Plus (all branch instructions are relative mode only)
    if (cpu.n == 0) {
      branch(mode, cpu);
    }
  }
  void Instruction::Bmi(const AddressMode &mode, CPU &cpu) const {
    // Branch on Minus (all branch instructions are relative mode only)
    if (cpu.n == 1) {
      branch(mode, cpu);
    }
  }
  void Instruction::Bvc(const AddressMode &mode, CPU &cpu) const {
    // Branch on Overflow Clear (all branch instructions are relative mode only)
    if (cpu.v == 0) {
      branch(mode, cpu);
    }
  }
  void Instruction::Bvs(const AddressMode &mode, CPU &cpu) const {
    // Branch on Overflow Set (all branch instructions are relative mode only)
    if (cpu.v == 1) {
      branch(mode, cpu);
    }
  }
#pragma endregion BRANCHING

#pragma region JUMPS
  void Instruction::Jmp(const AddressMode &mode, CPU &cpu) const {
    // Jump absolute or indirect to address
    uint16_t address = mode.address(cpu);
    cpu.pc = address;
  }
  void Instruction::Jsr(const AddressMode &mode, CPU &cpu) const {
    // Jump to Subroutine
    uint16_t address = mode.address(cpu);
    uint16_t next_operation = cpu.pc;
    // push address-1 onto stack
    uint16_t byte_before_address = address - 1;
    // push high byte
    cpu.write_byte(StackBase + cpu.s, (byte_before_address >> 8));
    cpu.s--;
    // push low byte
    cpu.write_byte(StackBase + cpu.s, (byte_before_address & 0xFF));
    cpu.s--;

    cpu.pc = address;
  }
  void Instruction::Rts(const AddressMode &mode, CPU &cpu) const {
    // Return from Subroutine
    // pop bytes from stack
    cpu.s++;
    uint8_t lo_byte = cpu.read_byte(StackBase + cpu.s);
    cpu.s++;
    uint8_t hi_byte = cpu.read_byte(StackBase + cpu.s);
    uint16_t byte_before_address = (hi_byte << 8) | lo_byte;
    uint16_t address = byte_before_address + 1;

    cpu.pc = address;
  }
#pragma endregion JUMPS

#pragma region INTERRUPT
  void Instruction::Brk(const AddressMode &mode, CPU &cpu) const {
    cpu.b = 1;
    cpu.i = 1;
  }
  void Instruction::Rti(const AddressMode &mode, CPU &cpu) const {
    // Return from Interrupt

    // pop the P status register
    cpu.s++;
    cpu.p = cpu.read_byte(StackBase + cpu.s);

    // pop PC
    cpu.s++;
    uint8_t lo_byte = cpu.read_byte(StackBase + cpu.s);
    cpu.s++;
    uint8_t hi_byte = cpu.read_byte(StackBase + cpu.s);
    uint16_t address = (hi_byte << 8) | lo_byte;
    cpu.pc = address;
  }
#pragma endregion INTERRUPT

#pragma region OTHER
  void Instruction::Bit(const AddressMode &mode, CPU &cpu) const {
    uint8_t value = mode.value(cpu);

    set_z(cpu, value & cpu.a);
    set_n(cpu, value);
    cpu.v = bitN(value, 6);
  }
  void Instruction::Nop(const AddressMode &mode, CPU &cpu) const {
    cpu.logger().log(std::format("--{} DID NOTHING (AS EXPECTED)", name()));
  }
#pragma endregion OTHER

  // clang-format off
  const Instruction Instruction::ADC{"ADC", &Instruction::Adc};
  const Instruction Instruction::AND{"AND", &Instruction::And};
  const Instruction Instruction::ASL{"ASL", &Instruction::Asl};
  const Instruction Instruction::BCC{"BCC", &Instruction::Bcc};
  const Instruction Instruction::BCS{"BCS", &Instruction::Bcs};
  const Instruction Instruction::BEQ{"BEQ", &Instruction::Beq};
  const Instruction Instruction::BIT{"BIT", &Instruction::Bit};
  const Instruction Instruction::BMI{"BMI", &Instruction::Bmi};
  const Instruction Instruction::BNE{"BNE", &Instruction::Bne};
  const Instruction Instruction::BPL{"BPL", &Instruction::Bpl};
  const Instruction Instruction::BRK{"BRK", &Instruction::Brk};
  const Instruction Instruction::BVC{"BVC", &Instruction::Bvc};
  const Instruction Instruction::BVS{"BVS", &Instruction::Bvs};
  const Instruction Instruction::CLC{"CLC", &Instruction::Clc};
  const Instruction Instruction::CLD{"CLD", &Instruction::Cld};
  const Instruction Instruction::CLI{"CLI", &Instruction::Cli};
  const Instruction Instruction::CLV{"CLV", &Instruction::Clv};
  const Instruction Instruction::CMP{"CMP", &Instruction::Cmp};
  const Instruction Instruction::CPX{"CPX", &Instruction::Cpx};
  const Instruction Instruction::CPY{"CPY", &Instruction::Cpy};
  const Instruction Instruction::DEC{"DEC", &Instruction::Dec};
  const Instruction Instruction::DEX{"DEX", &Instruction::Dex};
  const Instruction Instruction::DEY{"DEY", &Instruction::Dey};
  const Instruction Instruction::EOR{"EOR", &Instruction::Eor};
  const Instruction Instruction::INC{"INC", &Instruction::Inc};
  const Instruction Instruction::INX{"INX", &Instruction::Inx};
  const Instruction Instruction::INY{"INY", &Instruction::Iny};
  const Instruction Instruction::JMP{"JMP", &Instruction::Jmp};
  const Instruction Instruction::JSR{"JSR", &Instruction::Jsr};
  const Instruction Instruction::LDA{"LDA", &Instruction::Lda};
  const Instruction Instruction::LDX{"LDX", &Instruction::Ldx};
  const Instruction Instruction::LDY{"LDY", &Instruction::Ldy};
  const Instruction Instruction::LSR{"LSR", &Instruction::Lsr};
  const Instruction Instruction::NOP{"NOP", &Instruction::Nop};
  const Instruction Instruction::ORA{"ORA", &Instruction::Ora};
  const Instruction Instruction::PHA{"PHA", &Instruction::Pha};
  const Instruction Instruction::PHP{"PHP", &Instruction::Php};
  const Instruction Instruction::PLA{"PLA", &Instruction::Pla};
  const Instruction Instruction::PLP{"PLP", &Instruction::Plp};
  const Instruction Instruction::ROL{"ROL", &Instruction::Rol};
  const Instruction Instruction::ROR{"ROR", &Instruction::Ror};
  const Instruction Instruction::RTI{"RTI", &Instruction::Rti};
  const Instruction Instruction::RTS{"RTS", &Instruction::Rts};
  const Instruction Instruction::SBC{"SBC", &Instruction::Sbc};
  const Instruction Instruction::SEC{"SEC", &Instruction::Sec};
  const Instruction Instruction::SED{"SED", &Instruction::Sed};
  const Instruction Instruction::SEI{"SEI", &Instruction::Sei};
  const Instruction Instruction::STA{"STA", &Instruction::Sta};
  const Instruction Instruction::STX{"STX", &Instruction::Stx};
  const Instruction Instruction::STY{"STY", &Instruction::Sty};
  const Instruction Instruction::TAX{"TAX", &Instruction::Tax};
  const Instruction Instruction::TAY{"TAY", &Instruction::Tay};
  const Instruction Instruction::TSX{"TSX", &Instruction::Tsx};
  const Instruction Instruction::TXA{"TXA", &Instruction::Txa};
  const Instruction Instruction::TXS{"TXS", &Instruction::Txs};
  const Instruction Instruction::TYA{"TYA", &Instruction::Tya};
  // clang-format on

}// namespace mos6502
