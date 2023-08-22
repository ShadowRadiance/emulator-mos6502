#include <src/mos6502/cpu.h>

#include <format>
#include <stdexcept>
#include <vector>
#include <string>

namespace mos6502
{
    CPU::Operation CPU::decode(uint8_t opcode)
    {
        switch (opcode)
        {
        case 0x00: // 00000000
            return {"BRK", "i"};
        case 0x06: // 00000110 = 000.001.10   000...10 = ASL, ...001.. = "zp"
            return {"ASL", "zp"};
        case 0x0A: // 00001010 = 000.010.10   000...10 = ASL, ...010.. = "A"
            return {"ASL", "A"};
        case 0x0E: // 00001110 = 000.011.10   000...10 = ASL, ...011.. = "a"
            return {"ASL", "a"};
        case 0x16: // 00010110 = 000.101.10   000...10 = ASL, ...101.. = "zp,x"
            return {"ASL", "zp,x"};
        case 0x1E: // 00011110 = 000.111.10   000...10 = ASL, ...111.. = "a,x"
            return {"ASL", "a,x"};
        case 0xA1: // 10100001 = 101.000.01   101...01 = LDA, ...000.. = "(zp,x)"
            return {"LDA", "(zp,x)"};
        case 0xA5: // 10100101 = 101.001.01   101...01 = LDA, ...001.. = "zp"
            return {"LDA", "zp"};
        case 0xA9: // 10101001 = 101.010.01   101...01 = LDA, ...010.. = "#"
            return {"LDA", "#"};
        case 0xAD: // 10101101 = 101.011.01   101...01 = LDA, ...011.. = "a"
            return {"LDA", "a"};
        case 0xB1: // 10110001 = 101.100.01   101...01 = LDA, ...100.. = "(zp),y"
            return {"LDA", "(zp),y"};
        case 0xB5: // 10110101 = 101.101.01   101...01 = LDA, ...101.. = "zp,x"
            return {"LDA", "zp,x"};
        case 0xB9: // 10111001 = 101.110.01   101...01 = LDA, ...110.. = "a,y"
            return {"LDA", "a,y"};
        case 0xBD: // 10111101 = 101.111.01   101...01 = LDA, ...111.. = "a,x"
            return {"LDA", "a,x"};
        case 0xEA: // 11101010
            return {"NOP", "i"};
        default:
            return lookup_by_parser(opcode);
        }
    }

    struct OpCodeParser
    {
        OpCodeParser(uint8_t opcode) { code = opcode; }

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

    const std::map<uint8_t, std::string> parsedCodes = {
        {0b000, "(zp,x)"},
        {0b001, "zp"},
        {0b010, "A"},
        {0b011, "a"},
        {0b100, "(zp),y"},
        {0b101, "zp,x"},
        {0b110, "a,y"},
        {0b111, "a,x"}};
    // const std::vector<std::string> parsedCodes = {"(zp,x)", "zp", "#", "a", "(zp),y", "zp,x", "a,y", "a,x"};

    const std::map<uint8_t, std::string> parsedInstructions = {
        {0b00010, "ASL"},
        {0b10101, "LDA"},
    };

    CPU::Operation CPU::lookup_by_parser(uint8_t opcode)
    {
        OpCodeParser parser{opcode};

        std::string addressMode = parsedCodes.at(parser.mode);
        auto it = parsedInstructions.find((parser.prefix << 2) | parser.suffix);
        if (it == parsedInstructions.end())
            throw std::invalid_argument(std::format("Invalid Opcode ${:02x}", opcode));
        std::string instruction = it->second;
        return {instruction, addressMode};
    }

}
