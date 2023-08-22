#include "./immediate.h"

namespace components
{
    namespace addressing
    {
        std::string Immediate::name() const { return "Immediate"; };
        std::string Immediate::code() const { return "#"; };
        uint16_t Immediate::resolve_address() const { return 0; };
        uint8_t Immediate::resolve_value() const { return 0; };
    }
}
