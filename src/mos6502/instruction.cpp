#include "instruction.h"

#include <format>
#include <src/mos6502/address_mode.h>
#include <src/mos6502/cpu.h>

namespace mos6502 {

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

#pragma region LOAD, STORE, TRANSFER
  void Instruction::Lda(const AddressMode &mode, CPU &cpu) const {
    // Load Value to A
    uint8_t value = mode.value(cpu);
    cpu.a = value;
    cpu.n = value >> 7;
    cpu.z = value == 0;
    cpu.logger().log(std::format("--{} WROTE ${:02x} to A register", name(), value));
  }
  void Instruction::Ldx(const AddressMode &mode, CPU &cpu) const {
    // Load Value to X
    uint8_t value = mode.value(cpu);
    cpu.x = value;
    cpu.n = value >> 7;
    cpu.z = value == 0;
    cpu.logger().log(std::format("--{} WROTE ${:02x} to X register", name(), value));
  }
  void Instruction::Ldy(const AddressMode &mode, CPU &cpu) const {
    // Load Value to Y
    uint8_t value = mode.value(cpu);
    cpu.y = value;
    cpu.n = value >> 7;
    cpu.z = value == 0;
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
    cpu.x = value;
    cpu.n = value >> 7;
    cpu.z = value == 0;
    cpu.logger().log(std::format("--{} WROTE A(${:02x}) to X", name(), value));
  }
  void Instruction::Tay(const AddressMode &mode, CPU &cpu) const {
    // Transfer A to Y
    uint8_t value = cpu.a;
    cpu.y = value;
    cpu.n = value >> 7;
    cpu.z = value == 0;
    cpu.logger().log(std::format("--{} WROTE A(${:02x}) to Y", name(), value));
  }
  void Instruction::Tsx(const AddressMode &mode, CPU &cpu) const {
    // Transfer S to X
    uint8_t value = cpu.s;
    cpu.x = value;
    cpu.n = value >> 7;
    cpu.z = value == 0;
    cpu.logger().log(std::format("--{} WROTE S(${:02x}) to X", name(), value));
  }
  void Instruction::Txa(const AddressMode &mode, CPU &cpu) const {
    // Transfer X to A
    uint8_t value = cpu.x;
    cpu.a = value;
    cpu.n = value >> 7;
    cpu.z = value == 0;
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
    cpu.a = value;
    cpu.n = value >> 7;
    cpu.z = value == 0;
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
    value &= 0b00110000; // set bits 4 and 5
    cpu.write_byte(StackBase + cpu.s, value);
    cpu.s--;
  }
  void Instruction::Pla(const AddressMode &mode, CPU &cpu) const {
    // Pull A
    cpu.s++;
    uint8_t value = cpu.read_byte(StackBase + cpu.s);
    cpu.a = value;
    cpu.n = value >> 7;
    cpu.z = value == 0;
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
  void Instruction::Dec(const AddressMode &mode, CPU &cpu) const {}
  void Instruction::Dex(const AddressMode &mode, CPU &cpu) const {}
  void Instruction::Dey(const AddressMode &mode, CPU &cpu) const {}
  void Instruction::Inc(const AddressMode &mode, CPU &cpu) const {}
  void Instruction::Inx(const AddressMode &mode, CPU &cpu) const {}
  void Instruction::Iny(const AddressMode &mode, CPU &cpu) const {}
#pragma endregion INCREMENT, DECREMENT

#pragma region ARITHMETIC
  void Instruction::Adc(const AddressMode &mode, CPU &cpu) const {}
  void Instruction::Sbc(const AddressMode &mode, CPU &cpu) const {}
#pragma endregion ARITHMETIC

#pragma region LOGICAL
  void Instruction::And(const AddressMode &mode, CPU &cpu) const {}
  void Instruction::Eor(const AddressMode &mode, CPU &cpu) const {}
  void Instruction::Ora(const AddressMode &mode, CPU &cpu) const {}
#pragma endregion LOGICAL

#pragma region SHIFT, ROTATE
  void Instruction::Asl(const AddressMode &mode, CPU &cpu) const {}
  void Instruction::Lsr(const AddressMode &mode, CPU &cpu) const {
    // if operating on A, write result to A
    // if operating on address, write result to address
  }
  void Instruction::Rol(const AddressMode &mode, CPU &cpu) const {}
  void Instruction::Ror(const AddressMode &mode, CPU &cpu) const {}
#pragma endregion SHIFT, ROTATE

#pragma region FLAG
  void Instruction::Clc(const AddressMode &mode, CPU &cpu) const {}
  void Instruction::Cld(const AddressMode &mode, CPU &cpu) const {}
  void Instruction::Cli(const AddressMode &mode, CPU &cpu) const {}
  void Instruction::Clv(const AddressMode &mode, CPU &cpu) const {}
  void Instruction::Sec(const AddressMode &mode, CPU &cpu) const {}
  void Instruction::Sed(const AddressMode &mode, CPU &cpu) const {}
  void Instruction::Sei(const AddressMode &mode, CPU &cpu) const {}
#pragma endregion FLAG

#pragma region COMPARISON
  void Instruction::Cmp(const AddressMode &mode, CPU &cpu) const {}
  void Instruction::Cpx(const AddressMode &mode, CPU &cpu) const {}
  void Instruction::Cpy(const AddressMode &mode, CPU &cpu) const {}
#pragma endregion COMPARISON

#pragma region BRANCHING
  void Instruction::Bcc(const AddressMode &mode, CPU &cpu) const {}
  void Instruction::Bcs(const AddressMode &mode, CPU &cpu) const {}
  void Instruction::Beq(const AddressMode &mode, CPU &cpu) const {}
  void Instruction::Bmi(const AddressMode &mode, CPU &cpu) const {}
  void Instruction::Bne(const AddressMode &mode, CPU &cpu) const {}
  void Instruction::Bpl(const AddressMode &mode, CPU &cpu) const {}
  void Instruction::Bvc(const AddressMode &mode, CPU &cpu) const {}
  void Instruction::Bvs(const AddressMode &mode, CPU &cpu) const {}
#pragma endregion BRANCHING

#pragma region JUMPS
  void Instruction::Jmp(const AddressMode &mode, CPU &cpu) const {}
  void Instruction::Jsr(const AddressMode &mode, CPU &cpu) const {}
  void Instruction::Rts(const AddressMode &mode, CPU &cpu) const {}
#pragma endregion JUMPS

#pragma region INTERRUPT
  void Instruction::Brk(const AddressMode &mode, CPU &cpu) const {}
  void Instruction::Rti(const AddressMode &mode, CPU &cpu) const {}
#pragma endregion INTERRUPT

#pragma region OTHER
  void Instruction::Bit(const AddressMode &mode, CPU &cpu) const {}
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
