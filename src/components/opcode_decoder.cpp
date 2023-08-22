#include "./mos6502.h"

#include <format>

#include <src/components/opcode_parser.h>
#include <src/components/address_modes.h>
#include <src/components/operations.h>

namespace components
{
    std::unique_ptr<Operation> MOS6502::decode(uint8_t opcode)
    {
        OpCodeParser parser{opcode};

        switch (parser.code)
        {
        case 0x00:
            return std::make_unique<operations::BRK>(logger_);
        case 0xEA:
            return std::make_unique<operations::NOP>(logger_);
        default:
            throw std::invalid_argument(std::format("Invalid Opcode ${:02x}", opcode));
        }
    }

}
