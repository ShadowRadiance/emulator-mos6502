#include "./mos6502.h"

#include <format>
#include <stdexcept>

#include <src/components/opcode_parser.h>
#include <src/components/address_modes.h>
#include <src/components/operations.h>

namespace components
{
    std::map<std::string, std::unique_ptr<AddressMode>> init()
    {
        std::map<std::string, std::unique_ptr<AddressMode>> map;

        map["(a)"] = std::make_unique<addressing::AbsoluteIndirect>();
        map["a,x"] = std::make_unique<addressing::AbsoluteX>();
        map["a,y"] = std::make_unique<addressing::AbsoluteY>();
        map["a"] = std::make_unique<addressing::Absolute>();
        map["A"] = std::make_unique<addressing::Accumulator>();
        map["#"] = std::make_unique<addressing::Immediate>();
        map["i"] = std::make_unique<addressing::Implied>();
        map["r"] = std::make_unique<addressing::Relative>();
        map["(zp),y"] = std::make_unique<addressing::ZeroPageIndirectY>();
        map["(zp,x)"] = std::make_unique<addressing::ZeroPageXIndirect>();
        map["zp,x"] = std::make_unique<addressing::ZeroPageX>();
        map["zp,y"] = std::make_unique<addressing::ZeroPageY>();
        map["zp"] = std::make_unique<addressing::ZeroPage>();

        return map;
    }

    std::map<std::string, std::unique_ptr<AddressMode>> MOS6502::addressModes = init();

    std::unique_ptr<Operation> MOS6502::decode(uint8_t opcode)
    {
        switch (opcode)
        {
        case 0x00:
            return std::make_unique<operations::BRK>(*this, logger_);
        case 0x06:
            return std::make_unique<operations::ASL>(*this, logger_, *MOS6502::addressModes["zp"]);
        case 0x0A:
            return std::make_unique<operations::ASL>(*this, logger_, *MOS6502::addressModes["A"]);
        case 0x0E:
            return std::make_unique<operations::ASL>(*this, logger_, *MOS6502::addressModes["a"]);
        case 0x16:
            return std::make_unique<operations::ASL>(*this, logger_, *MOS6502::addressModes["zp,x"]);
        case 0x1E:
            return std::make_unique<operations::ASL>(*this, logger_, *MOS6502::addressModes["a,x"]);
        case 0xEA:
            return std::make_unique<operations::NOP>(*this, logger_);
        default:
            return lookup_by_parser(opcode);
        }
    }

    std::unique_ptr<Operation> MOS6502::lookup_by_parser(uint8_t opcode)
    {
        // OpCodeParser parser{opcode};

        // uint8_t addressModeCode = parser.mode;
        // AddressMode addressMode;

        throw std::invalid_argument(std::format("Invalid Opcode ${:02x}", opcode));
    }

}
