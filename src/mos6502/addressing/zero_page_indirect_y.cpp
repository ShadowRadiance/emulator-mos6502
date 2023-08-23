#include <src/mos6502/addressing/modes.h>

namespace mos6502 {
  namespace addressing {
    std::string ZeroPageIndirectY::name() const {
      return "ZeroPageIndirectY";
    }
    std::string ZeroPageIndirectY::code() const {
      return "(zp),y";
    }
    uint16_t ZeroPageIndirectY::resolve_address() const {
      return 0;
    }
    uint8_t ZeroPageIndirectY::resolve_value() const {
      return 0;
    }
  }// namespace addressing
}// namespace mos6502
