#include <src/mos6502/addressing/modes.h>

namespace mos6502
{
    namespace addressing
    {
        std::string Absolute::name() const { return "Absolute"; };
        std::string Absolute::code() const { return "a"; };
        uint16_t Absolute::resolve_address() const { return 0; };
        uint8_t Absolute::resolve_value() const { return 0; };
    }
}
