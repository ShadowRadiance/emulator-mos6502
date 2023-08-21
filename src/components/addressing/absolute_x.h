#pragma once

#include <src/components/interface.h>

namespace components
{
    namespace addressing
    {
        class AbsoluteX : public AddressMode
        {
            uint16_t resolve_address();
            uint8_t resolve_value();
        };

    } // namespace addressing

} // namespace components
