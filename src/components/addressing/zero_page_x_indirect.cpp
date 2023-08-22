#include "./zero_page_x_indirect.h"

namespace components
{
    namespace addressing
    {
        std::string ZeroPageXIndirect::name() const { return "ZeroPageXIndirect"; };
        std::string ZeroPageXIndirect::code() const { return "(zp,x)"; };
        uint16_t ZeroPageXIndirect::resolve_address() const { return 0; };
        uint8_t ZeroPageXIndirect::resolve_value() const { return 0; };
    }
}
