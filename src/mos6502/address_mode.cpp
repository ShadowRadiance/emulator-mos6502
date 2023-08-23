#include "address_mode.h"

namespace mos6502 {

  AddressMode::AddressMode(std::string name, std::string code) : name_(name), code_(code) {}
  std::string AddressMode::name() const {
    return name_;
  }
  std::string AddressMode::code() const {
    return code_;
  }
  bool AddressMode::operator==(const AddressMode &other) const {
    return &other == this;
  }

  const AddressMode AddressMode::AbsoluteIndirect{"AbsoluteIndirect", "(a)"};
  const AddressMode AddressMode::AbsoluteX{"AbsoluteX", "a,x"};
  const AddressMode AddressMode::AbsoluteY{"AbsoluteY", "a,y"};
  const AddressMode AddressMode::Absolute{"Absolute", "a"};
  const AddressMode AddressMode::Accumulator{"Accumulator", "A"};
  const AddressMode AddressMode::Immediate{"Immediate", "#"};
  const AddressMode AddressMode::Implied{"Implied", "i"};
  const AddressMode AddressMode::Relative{"Relative", "r"};
  const AddressMode AddressMode::ZeroPageIndirectY{"ZeroPageIndirectY", "(zp),y"};
  const AddressMode AddressMode::ZeroPageXIndirect{"ZeroPageXIndirect", "(zp,x)"};
  const AddressMode AddressMode::ZeroPageX{"ZeroPageX", "zp,x"};
  const AddressMode AddressMode::ZeroPageY{"ZeroPageY", "zp,y"};
  const AddressMode AddressMode::ZeroPage{"ZeroPage", "zp"};
}// namespace mos6502
