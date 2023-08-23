#include "address_mode.h"

#include <src/mos6502/cpu.h>
#include <stdexcept>

namespace mos6502 {

  AddressMode::AddressMode(
    std::string_view name,
    std::string_view code,
    ValueMemFn value_memfn,
    AddressMemFn address_mem_fn)
          : name_(name)
          , code_(code)
          , value_memfn_(value_memfn)
          , address_memfn_(address_mem_fn) {}

  std::string_view AddressMode::name() const {
    return name_;
  }

  std::string_view AddressMode::code() const {
    return code_;
  }

  bool AddressMode::operator==(const AddressMode &other) const {
    return &other == this;
  }

  uint8_t AddressMode::value(CPU &cpu) const {
    return (this->*value_memfn_)(cpu);
  }

  uint16_t AddressMode::address(CPU &cpu) const {
    return (this->*address_memfn_)(cpu);
  }

  uint8_t AddressMode::AbsoluteIndirectValue(CPU &cpu) const {
    return cpu.read_byte(AbsoluteIndirectAddress(cpu));
  }
  uint8_t AddressMode::AbsoluteXValue(CPU &cpu) const {
    return cpu.read_byte(AbsoluteXAddress(cpu));
  }
  uint8_t AddressMode::AbsoluteYValue(CPU &cpu) const {
    return cpu.read_byte(AbsoluteYAddress(cpu));
  }
  uint8_t AddressMode::AbsoluteValue(CPU &cpu) const {
    return cpu.read_byte(AbsoluteAddress(cpu));
  }
  uint8_t AddressMode::AccumulatorValue(CPU &cpu) const {
    return cpu.a;
  }
  uint8_t AddressMode::ImmediateValue(CPU &cpu) const {
    return cpu.fetch_pc_byte();
  }
  uint8_t AddressMode::ImpliedValue(CPU &cpu) const {
    throw std::logic_error("Do not call value in implied mode");
  }
  uint8_t AddressMode::RelativeValue(CPU &cpu) const {
    throw std::logic_error("Do not call value in relative mode");
  }
  uint8_t AddressMode::ZeroPageIndirectYValue(CPU &cpu) const {
    return cpu.read_byte(ZeroPageIndirectYAddress(cpu));
  }
  uint8_t AddressMode::ZeroPageXIndirectValue(CPU &cpu) const {
    return cpu.read_byte(ZeroPageXIndirectAddress(cpu));
  }
  uint8_t AddressMode::ZeroPageXValue(CPU &cpu) const {
    return cpu.read_byte(ZeroPageXAddress(cpu));
  }
  uint8_t AddressMode::ZeroPageYValue(CPU &cpu) const {
    return cpu.read_byte(ZeroPageYAddress(cpu));
  }
  uint8_t AddressMode::ZeroPageValue(CPU &cpu) const {
    return cpu.read_byte(ZeroPageAddress(cpu));
  }

  uint16_t AddressMode::AbsoluteIndirectAddress(CPU &cpu) const {
    return cpu.read_word(AbsoluteAddress(cpu));
  }
  uint16_t AddressMode::AbsoluteXAddress(CPU &cpu) const {
    return AbsoluteAddress(cpu) + cpu.x;
  }
  uint16_t AddressMode::AbsoluteYAddress(CPU &cpu) const {
    return AbsoluteAddress(cpu) + cpu.y;
  }
  uint16_t AddressMode::AbsoluteAddress(CPU &cpu) const {
    return cpu.fetch_pc_word();
  }
  uint16_t AddressMode::AccumulatorAddress(CPU &cpu) const {
    throw std::logic_error("Do not call address in accumulator mode");
  }
  uint16_t AddressMode::ImmediateAddress(CPU &cpu) const {
    throw std::logic_error("Do not call address in immediate mode");
  }
  uint16_t AddressMode::ImpliedAddress(CPU &cpu) const {
    throw std::logic_error("Do not call address in implied mode");
  }
  uint16_t AddressMode::RelativeAddress(CPU &cpu) const {
    return cpu.pc - 1u + int8_t(cpu.fetch_pc_byte());
  }
  uint16_t AddressMode::ZeroPageIndirectYAddress(CPU &cpu) const {
    return cpu.read_word(cpu.fetch_pc_byte()) + cpu.y;
  }
  uint16_t AddressMode::ZeroPageXIndirectAddress(CPU &cpu) const {
    return cpu.read_word(cpu.fetch_pc_byte() + cpu.x);
  }
  uint16_t AddressMode::ZeroPageXAddress(CPU &cpu) const {
    return ZeroPageAddress(cpu) + cpu.x;
  }
  uint16_t AddressMode::ZeroPageYAddress(CPU &cpu) const {
    return ZeroPageAddress(cpu) + cpu.y;
  }
  uint16_t AddressMode::ZeroPageAddress(CPU &cpu) const {
    return cpu.fetch_pc_byte();
  }

  // clang-format off
  const AddressMode AddressMode::AbsoluteIndirect  { "AbsoluteIndirect"  , "(a)"    , &AddressMode::AbsoluteIndirectValue  , &AddressMode::AbsoluteIndirectAddress  };
  const AddressMode AddressMode::AbsoluteX         { "AbsoluteX"         , "a,x"    , &AddressMode::AbsoluteXValue         , &AddressMode::AbsoluteXAddress         };
  const AddressMode AddressMode::AbsoluteY         { "AbsoluteY"         , "a,y"    , &AddressMode::AbsoluteYValue         , &AddressMode::AbsoluteYAddress         };
  const AddressMode AddressMode::Absolute          { "Absolute"          , "a"      , &AddressMode::AbsoluteValue          , &AddressMode::AbsoluteAddress          };
  const AddressMode AddressMode::Accumulator       { "Accumulator"       , "A"      , &AddressMode::AccumulatorValue       , &AddressMode::AccumulatorAddress       };
  const AddressMode AddressMode::Immediate         { "Immediate"         , "#"      , &AddressMode::ImmediateValue         , &AddressMode::ImmediateAddress         };
  const AddressMode AddressMode::Implied           { "Implied"           , "i"      , &AddressMode::ImpliedValue           , &AddressMode::ImpliedAddress           };
  const AddressMode AddressMode::Relative          { "Relative"          , "r"      , &AddressMode::RelativeValue          , &AddressMode::RelativeAddress          };
  const AddressMode AddressMode::ZeroPageIndirectY { "ZeroPageIndirectY" , "(zp),y" , &AddressMode::ZeroPageIndirectYValue , &AddressMode::ZeroPageIndirectYAddress };
  const AddressMode AddressMode::ZeroPageXIndirect { "ZeroPageXIndirect" , "(zp,x)" , &AddressMode::ZeroPageXIndirectValue , &AddressMode::ZeroPageXIndirectAddress };
  const AddressMode AddressMode::ZeroPageX         { "ZeroPageX"         , "zp,x"   , &AddressMode::ZeroPageXValue         , &AddressMode::ZeroPageXAddress         };
  const AddressMode AddressMode::ZeroPageY         { "ZeroPageY"         , "zp,y"   , &AddressMode::ZeroPageYValue         , &AddressMode::ZeroPageYAddress         };
  const AddressMode AddressMode::ZeroPage          { "ZeroPage"          , "zp"     , &AddressMode::ZeroPageValue          , &AddressMode::ZeroPageAddress          };
  // clang-format on

}// namespace mos6502
