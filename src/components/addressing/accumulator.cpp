#include "./accumulator.h"

namespace components
{
    namespace addressing
    {
        std::string Accumulator::name() const { return "Accumulator"; };
        std::string Accumulator::code() const { return "A"; };
        uint16_t Accumulator::resolve_address() const { return 0; };
        uint8_t Accumulator::resolve_value() const { return 0; };
    }
}
