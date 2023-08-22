#pragma once

#include <cstdint>

namespace components
{
    class OpCodeParser
    {
    public:
        OpCodeParser(uint8_t opcode);

        union
        {
            uint8_t code;
            struct
            {
                uint8_t prefix : 3;
                uint8_t mode : 3;
                uint8_t suffix : 2;
            };
        };
    };
}
