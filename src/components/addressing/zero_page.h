#pragma once

#include <src/components/interface.h>

namespace components
{
    namespace addressing
    {
        class ZeroPage : public AddressMode
        {
            std::string name() const override;
            std::string code() const override;
            uint16_t resolve_address() const override;
            uint8_t resolve_value() const override;
        };

    } // namespace addressing

} // namespace components
