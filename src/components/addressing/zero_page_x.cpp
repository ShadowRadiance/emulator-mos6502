#include "./zero_page_x.h"

namespace components
{
    namespace addressing
    {
        std::string ZeroPageX::name() const { return "ZeroPageX"; };
        std::string ZeroPageX::code() const { return "zp,x"; };
        uint16_t ZeroPageX::resolve_address() const { return 0; };
        uint8_t ZeroPageX::resolve_value() const { return 0; };
    }
}
