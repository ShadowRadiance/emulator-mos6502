#include <src/mos6502/addressing/modes.h>

namespace mos6502 {
  namespace addressing {
    std::string ZeroPageY::name() const {
      return "ZeroPageY";
    }
    std::string ZeroPageY::code() const {
      return "zp,y";
    }
    uint16_t ZeroPageY::resolve_address() const {
      return 0;
    }
    uint8_t ZeroPageY::resolve_value() const {
      return 0;
    }
  }// namespace addressing
}// namespace mos6502
