#pragma once

#include <string>
#include <string_view>

namespace mos6502 {
  class CPU;

  class AddressMode
  {
  public:
    using ValueMemFn = uint8_t (AddressMode::*)(mos6502::CPU &cpu) const;
    using AddressMemFn = uint16_t (AddressMode::*)(mos6502::CPU &cpu) const;

    AddressMode(std::string_view name, std::string_view code, ValueMemFn value_memfn, AddressMemFn address_memfn);
    std::string_view name() const;
    std::string_view code() const;
    bool operator==(const AddressMode &other) const;

    uint16_t address(CPU &cpu) const;
    uint8_t value(CPU &cpu) const;

  private:
    std::string_view name_;
    std::string_view code_;
    ValueMemFn value_memfn_;
    AddressMemFn address_memfn_;

    uint16_t AbsoluteIndirectAddress(CPU &cpu) const;
    uint16_t AbsoluteXAddress(CPU &cpu) const;
    uint16_t AbsoluteYAddress(CPU &cpu) const;
    uint16_t AbsoluteAddress(CPU &cpu) const;
    uint16_t AccumulatorAddress(CPU &cpu) const;
    uint16_t ImmediateAddress(CPU &cpu) const;
    uint16_t ImpliedAddress(CPU &cpu) const;
    uint16_t RelativeAddress(CPU &cpu) const;
    uint16_t ZeroPageIndirectYAddress(CPU &cpu) const;
    uint16_t ZeroPageXIndirectAddress(CPU &cpu) const;
    uint16_t ZeroPageXAddress(CPU &cpu) const;
    uint16_t ZeroPageYAddress(CPU &cpu) const;
    uint16_t ZeroPageAddress(CPU &cpu) const;
    uint8_t AbsoluteIndirectValue(CPU &cpu) const;
    uint8_t AbsoluteXValue(CPU &cpu) const;
    uint8_t AbsoluteYValue(CPU &cpu) const;
    uint8_t AbsoluteValue(CPU &cpu) const;
    uint8_t AccumulatorValue(CPU &cpu) const;
    uint8_t ImmediateValue(CPU &cpu) const;
    uint8_t ImpliedValue(CPU &cpu) const;
    uint8_t RelativeValue(CPU &cpu) const;
    uint8_t ZeroPageIndirectYValue(CPU &cpu) const;
    uint8_t ZeroPageXIndirectValue(CPU &cpu) const;
    uint8_t ZeroPageXValue(CPU &cpu) const;
    uint8_t ZeroPageYValue(CPU &cpu) const;
    uint8_t ZeroPageValue(CPU &cpu) const;

  public:
    static const AddressMode AbsoluteIndirect;
    static const AddressMode AbsoluteX;
    static const AddressMode AbsoluteY;
    static const AddressMode Absolute;
    static const AddressMode Accumulator;
    static const AddressMode Immediate;
    static const AddressMode Implied;
    static const AddressMode Relative;
    static const AddressMode ZeroPageIndirectY;
    static const AddressMode ZeroPageXIndirect;
    static const AddressMode ZeroPageX;
    static const AddressMode ZeroPageY;
    static const AddressMode ZeroPage;
  };
}// namespace mos6502
