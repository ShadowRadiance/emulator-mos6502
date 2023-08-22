#include "./mos6502.h"

#include <format>

#include <src/components/opcode_parser.h>
#include <src/components/address_modes.h>
#include <src/components/operations.h>

namespace components
{
    std::unique_ptr<Operation> MOS6502::decode(uint8_t opcode)
    {
        switch (opcode)
        {
        case 0x00:
            return std::make_unique<operations::BRK>(logger_);
        // NONONO - cannot pass temp to a ref param!
        // Change ref param to ... uniqptr?
        // case 0x06:
        //     return std::make_unique<operations::ASL>(logger_, addressing::ZeroPage{});
        // case 0x0A:
        //     return std::make_unique<operations::ASL>(logger_, addressing::Accumulator{});
        // case 0x0E:
        //     return std::make_unique<operations::ASL>(logger_, addressing::Absolute{});
        // case 0x16:
        //     return std::make_unique<operations::ASL>(logger_, addressing::ZeroPageX{});
        // case 0x1E:
        //     return std::make_unique<operations::ASL>(logger_, addressing::AbsoluteX{});
        // case 0xEA:
        //     return std::make_unique<operations::NOP>(logger_);
        default:
            return lookup_by_parser(opcode);
        }
    }

    std::unique_ptr<Operation> MOS6502::lookup_by_parser(uint8_t opcode)
    {
        OpCodeParser parser{opcode};

        uint8_t addressModeCode = parser.mode;
        AddressMode addressMode;

        throw std::invalid_argument(std::format("Invalid Opcode ${:02x}", opcode));
    }

}
