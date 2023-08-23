#include "address_mode.h"

#include <src/mos6502/cpu.h>

namespace mos6502 {

  AddressMode::AddressMode(std::string_view name, std::string_view code, ValueMemFn value_memfn)
          : name_(name)
          , code_(code)
          , value_memfn_(value_memfn) {}

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

  uint8_t AddressMode::AbsoluteIndirectValue(CPU &cpu) const {
    return 0;
  }
  uint8_t AddressMode::AbsoluteXValue(CPU &cpu) const {
    return 0;
  }
  uint8_t AddressMode::AbsoluteYValue(CPU &cpu) const {
    return 0;
  }
  uint8_t AddressMode::AbsoluteValue(CPU &cpu) const {
    return 0;
  }
  uint8_t AddressMode::AccumulatorValue(CPU &cpu) const {
    return 0;
  }
  uint8_t AddressMode::ImmediateValue(CPU &cpu) const {
    return cpu.fetch_pc_byte();
  }
  uint8_t AddressMode::ImpliedValue(CPU &cpu) const {
    return 0;
  }
  uint8_t AddressMode::RelativeValue(CPU &cpu) const {
    return 0;
  }
  uint8_t AddressMode::ZeroPageIndirectYValue(CPU &cpu) const {
    return 0;
  }
  uint8_t AddressMode::ZeroPageXIndirectValue(CPU &cpu) const {
    return 0;
  }
  uint8_t AddressMode::ZeroPageXValue(CPU &cpu) const {
    return 0;
  }
  uint8_t AddressMode::ZeroPageYValue(CPU &cpu) const {
    return 0;
  }
  uint8_t AddressMode::ZeroPageValue(CPU &cpu) const {
    return 0;
  }

  // clang-format off
  const AddressMode AddressMode::AbsoluteIndirect  { "AbsoluteIndirect"  , "(a)"    , &AddressMode::AbsoluteIndirectValue  };
  const AddressMode AddressMode::AbsoluteX         { "AbsoluteX"         , "a,x"    , &AddressMode::AbsoluteXValue         };
  const AddressMode AddressMode::AbsoluteY         { "AbsoluteY"         , "a,y"    , &AddressMode::AbsoluteYValue         };
  const AddressMode AddressMode::Absolute          { "Absolute"          , "a"      , &AddressMode::AbsoluteValue          };
  const AddressMode AddressMode::Accumulator       { "Accumulator"       , "A"      , &AddressMode::AccumulatorValue       };
  const AddressMode AddressMode::Immediate         { "Immediate"         , "#"      , &AddressMode::ImmediateValue         };
  const AddressMode AddressMode::Implied           { "Implied"           , "i"      , &AddressMode::ImpliedValue           };
  const AddressMode AddressMode::Relative          { "Relative"          , "r"      , &AddressMode::RelativeValue          };
  const AddressMode AddressMode::ZeroPageIndirectY { "ZeroPageIndirectY" , "(zp),y" , &AddressMode::ZeroPageIndirectYValue };
  const AddressMode AddressMode::ZeroPageXIndirect { "ZeroPageXIndirect" , "(zp,x)" , &AddressMode::ZeroPageXIndirectValue };
  const AddressMode AddressMode::ZeroPageX         { "ZeroPageX"         , "zp,x"   , &AddressMode::ZeroPageXValue         };
  const AddressMode AddressMode::ZeroPageY         { "ZeroPageY"         , "zp,y"   , &AddressMode::ZeroPageYValue         };
  const AddressMode AddressMode::ZeroPage          { "ZeroPage"          , "zp"     , &AddressMode::ZeroPageValue          };
  // clang-format on

}// namespace mos6502
