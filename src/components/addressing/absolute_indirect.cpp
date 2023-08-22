#include "./absolute_indirect.h"

namespace components
{
    namespace addressing
    {
        std::string AbsoluteIndirect::name() const { return "AbsoluteIndirect"; };
        std::string AbsoluteIndirect::code() const { return "(a)"; };
        uint16_t AbsoluteIndirect::resolve_address() const { return 0; };
        uint8_t AbsoluteIndirect::resolve_value() const { return 0; };
    }
}
