#include "instruction.h"

#include <format>
#include <src/mos6502/address_mode.h>
#include <src/mos6502/cpu.h>

namespace mos6502 {

  Instruction::Instruction(std::string name, MemFn memfn) : name_(name), memfn_(memfn) {}

  std::string Instruction::name() const {
    return name_;
  }

  bool Instruction::operator==(const Instruction &other) const {
    return &other == this;
  }

  void Instruction::execute(const AddressMode &addressMode, mos6502::CPU &cpu) const {
    cpu.logger().log(std::format("{} {}", name(), addressMode.code()));
    (this->*memfn_)(addressMode, cpu);
  }

  void Instruction::Adc(const AddressMode &mode, mos6502::CPU &cpu) const {}
  void Instruction::And(const AddressMode &mode, mos6502::CPU &cpu) const {}
  void Instruction::Asl(const AddressMode &mode, mos6502::CPU &cpu) const {}
  void Instruction::Bcc(const AddressMode &mode, mos6502::CPU &cpu) const {}
  void Instruction::Bcs(const AddressMode &mode, mos6502::CPU &cpu) const {}
  void Instruction::Beq(const AddressMode &mode, mos6502::CPU &cpu) const {}
  void Instruction::Bit(const AddressMode &mode, mos6502::CPU &cpu) const {}
  void Instruction::Bmi(const AddressMode &mode, mos6502::CPU &cpu) const {}
  void Instruction::Bne(const AddressMode &mode, mos6502::CPU &cpu) const {}
  void Instruction::Bpl(const AddressMode &mode, mos6502::CPU &cpu) const {}
  void Instruction::Brk(const AddressMode &mode, mos6502::CPU &cpu) const {}
  void Instruction::Bvc(const AddressMode &mode, mos6502::CPU &cpu) const {}
  void Instruction::Bvs(const AddressMode &mode, mos6502::CPU &cpu) const {}
  void Instruction::Clc(const AddressMode &mode, mos6502::CPU &cpu) const {}
  void Instruction::Cld(const AddressMode &mode, mos6502::CPU &cpu) const {}
  void Instruction::Cli(const AddressMode &mode, mos6502::CPU &cpu) const {}
  void Instruction::Clv(const AddressMode &mode, mos6502::CPU &cpu) const {}
  void Instruction::Cmp(const AddressMode &mode, mos6502::CPU &cpu) const {}
  void Instruction::Cpx(const AddressMode &mode, mos6502::CPU &cpu) const {}
  void Instruction::Cpy(const AddressMode &mode, mos6502::CPU &cpu) const {}
  void Instruction::Dec(const AddressMode &mode, mos6502::CPU &cpu) const {}
  void Instruction::Dex(const AddressMode &mode, mos6502::CPU &cpu) const {}
  void Instruction::Dey(const AddressMode &mode, mos6502::CPU &cpu) const {}
  void Instruction::Eor(const AddressMode &mode, mos6502::CPU &cpu) const {}
  void Instruction::Inc(const AddressMode &mode, mos6502::CPU &cpu) const {}
  void Instruction::Inx(const AddressMode &mode, mos6502::CPU &cpu) const {}
  void Instruction::Iny(const AddressMode &mode, mos6502::CPU &cpu) const {}
  void Instruction::Jmp(const AddressMode &mode, mos6502::CPU &cpu) const {}
  void Instruction::Jsr(const AddressMode &mode, mos6502::CPU &cpu) const {}
  void Instruction::Lda(const AddressMode &mode, mos6502::CPU &cpu) const {
    cpu.a = 0x42;
  }
  void Instruction::Ldx(const AddressMode &mode, mos6502::CPU &cpu) const {}
  void Instruction::Ldy(const AddressMode &mode, mos6502::CPU &cpu) const {}
  void Instruction::Lsr(const AddressMode &mode, mos6502::CPU &cpu) const {}
  void Instruction::Nop(const AddressMode &mode, mos6502::CPU &cpu) const {}
  void Instruction::Ora(const AddressMode &mode, mos6502::CPU &cpu) const {}
  void Instruction::Pha(const AddressMode &mode, mos6502::CPU &cpu) const {}
  void Instruction::Php(const AddressMode &mode, mos6502::CPU &cpu) const {}
  void Instruction::Pla(const AddressMode &mode, mos6502::CPU &cpu) const {}
  void Instruction::Plp(const AddressMode &mode, mos6502::CPU &cpu) const {}
  void Instruction::Rol(const AddressMode &mode, mos6502::CPU &cpu) const {}
  void Instruction::Ror(const AddressMode &mode, mos6502::CPU &cpu) const {}
  void Instruction::Rti(const AddressMode &mode, mos6502::CPU &cpu) const {}
  void Instruction::Rts(const AddressMode &mode, mos6502::CPU &cpu) const {}
  void Instruction::Sbc(const AddressMode &mode, mos6502::CPU &cpu) const {}
  void Instruction::Sec(const AddressMode &mode, mos6502::CPU &cpu) const {}
  void Instruction::Sed(const AddressMode &mode, mos6502::CPU &cpu) const {}
  void Instruction::Sei(const AddressMode &mode, mos6502::CPU &cpu) const {}
  void Instruction::Sta(const AddressMode &mode, mos6502::CPU &cpu) const {}
  void Instruction::Stx(const AddressMode &mode, mos6502::CPU &cpu) const {}
  void Instruction::Sty(const AddressMode &mode, mos6502::CPU &cpu) const {}
  void Instruction::Tax(const AddressMode &mode, mos6502::CPU &cpu) const {}
  void Instruction::Tay(const AddressMode &mode, mos6502::CPU &cpu) const {}
  void Instruction::Tsx(const AddressMode &mode, mos6502::CPU &cpu) const {}
  void Instruction::Txa(const AddressMode &mode, mos6502::CPU &cpu) const {}
  void Instruction::Txs(const AddressMode &mode, mos6502::CPU &cpu) const {}
  void Instruction::Tya(const AddressMode &mode, mos6502::CPU &cpu) const {}

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
}// namespace mos6502
