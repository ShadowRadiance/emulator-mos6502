#pragma once

#include <string>

namespace mos6502 {
  class AddressMode;
  class CPU;

  class Instruction
  {
  public:
    using MemFn = void (Instruction::*)(const AddressMode &addressMode, mos6502::CPU &cpu) const;

    Instruction(std::string_view name, MemFn memfn);
    std::string_view name() const;
    bool operator==(const Instruction &other) const;
    void execute(const AddressMode &addressMode, mos6502::CPU &cpu) const;

  private:
    std::string_view name_;
    const MemFn memfn_;

    void set_a(CPU &cpu, uint8_t value) const;
    void set_x(CPU &cpu, uint8_t value) const;
    void set_y(CPU &cpu, uint8_t value) const;

    void set_c(CPU &cpu, uint16_t value_with_carry) const;
    void set_n(CPU &cpu, uint8_t value) const;
    void set_v(CPU &cpu, uint8_t value, uint8_t op1, uint8_t op2) const;
    void set_z(CPU &cpu, uint8_t value) const;

    void branch(const AddressMode &mode, CPU &cpu) const;

    void Adc(const AddressMode &mode, mos6502::CPU &cpu) const;
    void And(const AddressMode &mode, mos6502::CPU &cpu) const;
    void Asl(const AddressMode &mode, mos6502::CPU &cpu) const;
    void Bcc(const AddressMode &mode, mos6502::CPU &cpu) const;
    void Bcs(const AddressMode &mode, mos6502::CPU &cpu) const;
    void Beq(const AddressMode &mode, mos6502::CPU &cpu) const;
    void Bit(const AddressMode &mode, mos6502::CPU &cpu) const;
    void Bmi(const AddressMode &mode, mos6502::CPU &cpu) const;
    void Bne(const AddressMode &mode, mos6502::CPU &cpu) const;
    void Bpl(const AddressMode &mode, mos6502::CPU &cpu) const;
    void Brk(const AddressMode &mode, mos6502::CPU &cpu) const;
    void Bvc(const AddressMode &mode, mos6502::CPU &cpu) const;
    void Bvs(const AddressMode &mode, mos6502::CPU &cpu) const;
    void Clc(const AddressMode &mode, mos6502::CPU &cpu) const;
    void Cld(const AddressMode &mode, mos6502::CPU &cpu) const;
    void Cli(const AddressMode &mode, mos6502::CPU &cpu) const;
    void Clv(const AddressMode &mode, mos6502::CPU &cpu) const;
    void Cmp(const AddressMode &mode, mos6502::CPU &cpu) const;
    void Cpx(const AddressMode &mode, mos6502::CPU &cpu) const;
    void Cpy(const AddressMode &mode, mos6502::CPU &cpu) const;
    void Dec(const AddressMode &mode, mos6502::CPU &cpu) const;
    void Dex(const AddressMode &mode, mos6502::CPU &cpu) const;
    void Dey(const AddressMode &mode, mos6502::CPU &cpu) const;
    void Eor(const AddressMode &mode, mos6502::CPU &cpu) const;
    void Inc(const AddressMode &mode, mos6502::CPU &cpu) const;
    void Inx(const AddressMode &mode, mos6502::CPU &cpu) const;
    void Iny(const AddressMode &mode, mos6502::CPU &cpu) const;
    void Jmp(const AddressMode &mode, mos6502::CPU &cpu) const;
    void Jsr(const AddressMode &mode, mos6502::CPU &cpu) const;
    void Lda(const AddressMode &mode, mos6502::CPU &cpu) const;
    void Ldx(const AddressMode &mode, mos6502::CPU &cpu) const;
    void Ldy(const AddressMode &mode, mos6502::CPU &cpu) const;
    void Lsr(const AddressMode &mode, mos6502::CPU &cpu) const;
    void Nop(const AddressMode &mode, mos6502::CPU &cpu) const;
    void Ora(const AddressMode &mode, mos6502::CPU &cpu) const;
    void Pha(const AddressMode &mode, mos6502::CPU &cpu) const;
    void Php(const AddressMode &mode, mos6502::CPU &cpu) const;
    void Pla(const AddressMode &mode, mos6502::CPU &cpu) const;
    void Plp(const AddressMode &mode, mos6502::CPU &cpu) const;
    void Rol(const AddressMode &mode, mos6502::CPU &cpu) const;
    void Ror(const AddressMode &mode, mos6502::CPU &cpu) const;
    void Rti(const AddressMode &mode, mos6502::CPU &cpu) const;
    void Rts(const AddressMode &mode, mos6502::CPU &cpu) const;
    void Sbc(const AddressMode &mode, mos6502::CPU &cpu) const;
    void Sec(const AddressMode &mode, mos6502::CPU &cpu) const;
    void Sed(const AddressMode &mode, mos6502::CPU &cpu) const;
    void Sei(const AddressMode &mode, mos6502::CPU &cpu) const;
    void Sta(const AddressMode &mode, mos6502::CPU &cpu) const;
    void Stx(const AddressMode &mode, mos6502::CPU &cpu) const;
    void Sty(const AddressMode &mode, mos6502::CPU &cpu) const;
    void Tax(const AddressMode &mode, mos6502::CPU &cpu) const;
    void Tay(const AddressMode &mode, mos6502::CPU &cpu) const;
    void Tsx(const AddressMode &mode, mos6502::CPU &cpu) const;
    void Txa(const AddressMode &mode, mos6502::CPU &cpu) const;
    void Txs(const AddressMode &mode, mos6502::CPU &cpu) const;
    void Tya(const AddressMode &mode, mos6502::CPU &cpu) const;

  public:
    static const Instruction ADC;
    static const Instruction AND;
    static const Instruction ASL;
    static const Instruction BCC;
    static const Instruction BCS;
    static const Instruction BEQ;
    static const Instruction BIT;
    static const Instruction BMI;
    static const Instruction BNE;
    static const Instruction BPL;
    static const Instruction BRK;
    static const Instruction BVC;
    static const Instruction BVS;
    static const Instruction CLC;
    static const Instruction CLD;
    static const Instruction CLI;
    static const Instruction CLV;
    static const Instruction CMP;
    static const Instruction CPX;
    static const Instruction CPY;
    static const Instruction DEC;
    static const Instruction DEX;
    static const Instruction DEY;
    static const Instruction EOR;
    static const Instruction INC;
    static const Instruction INX;
    static const Instruction INY;
    static const Instruction JMP;
    static const Instruction JSR;
    static const Instruction LDA;
    static const Instruction LDX;
    static const Instruction LDY;
    static const Instruction LSR;
    static const Instruction NOP;
    static const Instruction ORA;
    static const Instruction PHA;
    static const Instruction PHP;
    static const Instruction PLA;
    static const Instruction PLP;
    static const Instruction ROL;
    static const Instruction ROR;
    static const Instruction RTI;
    static const Instruction RTS;
    static const Instruction SBC;
    static const Instruction SEC;
    static const Instruction SED;
    static const Instruction SEI;
    static const Instruction STA;
    static const Instruction STX;
    static const Instruction STY;
    static const Instruction TAX;
    static const Instruction TAY;
    static const Instruction TSX;
    static const Instruction TXA;
    static const Instruction TXS;
    static const Instruction TYA;
  };
}// namespace mos6502
