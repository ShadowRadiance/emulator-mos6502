#include "./absolute_y.h"

namespace components
{
    namespace addressing
    {
        std::string AbsoluteY::name() const { return "AbsoluteY"; };
        std::string AbsoluteY::code() const { return "a,y"; };
        uint16_t AbsoluteY::resolve_address() const { return 0; };
        uint8_t AbsoluteY::resolve_value() const { return 0; };
    }
}
