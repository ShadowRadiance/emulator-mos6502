#include "./implied.h"

namespace components
{
    namespace addressing
    {
        std::string Implied::name() const { return "Implied"; };
        std::string Implied::code() const { return "i"; };
        uint16_t Implied::resolve_address() const { return 0; };
        uint8_t Implied::resolve_value() const { return 0; };
    }
}
