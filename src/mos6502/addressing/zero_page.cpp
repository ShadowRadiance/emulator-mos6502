#include <src/mos6502/addressing/modes.h>

namespace mos6502 {
  namespace addressing {
    std::string ZeroPage::name() const {
      return "ZeroPage";
    }
    std::string ZeroPage::code() const {
      return "zp";
    }
    uint16_t ZeroPage::resolve_address() const {
      return 0;
    }
    uint8_t ZeroPage::resolve_value() const {
      return 0;
    }
  }// namespace addressing
}// namespace mos6502
