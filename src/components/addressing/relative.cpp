#include "./relative.h"

namespace components
{
    namespace addressing
    {
        std::string Relative::name() const { return "Relative"; };
        std::string Relative::code() const { return "r"; };
        uint16_t Relative::resolve_address() const { return 0; };
        uint8_t Relative::resolve_value() const { return 0; };
    }
}
