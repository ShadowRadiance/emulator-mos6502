#include <src/mos6502/addressing/modes.h>

namespace mos6502 {
  namespace addressing {
    std::string AbsoluteX::name() const {
      return "AbsoluteX";
    }
    std::string AbsoluteX::code() const {
      return "a,x";
    }
    uint16_t AbsoluteX::resolve_address() const {
      return 0;
    }
    uint8_t AbsoluteX::resolve_value() const {
      return 0;
    }
  }// namespace addressing
}// namespace mos6502
