#pragma once

#include <string>

namespace mos6502 {
  class AddressMode
  {
  public:
    AddressMode(std::string name, std::string code);
    std::string name() const;
    std::string code() const;
    bool operator==(const AddressMode &other) const;

  private:
    std::string name_;
    std::string code_;

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
