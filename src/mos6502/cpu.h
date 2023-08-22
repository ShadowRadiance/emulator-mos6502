#pragma once

#include <cstdint>
#include <memory>
#include <map>

#include <src/emulator/logger.h>
#include <src/emulator/memory.h>
#include <src/emulator/cpu.h>

namespace mos6502
{
    class CPU : public emulator::CPU
    {
    public:
        CPU(emulator::WritableMemory &mem, emulator::Logger &logger);
        void reset();
        bool tick();

    private:
        emulator::WritableMemory &mem_;
        emulator::Logger &logger_;

        uint8_t a;   // Accumulator
        uint8_t x;   // General Purpose Register
        uint8_t y;   // General Purpose Register
        uint8_t s;   // Stack Offset
        uint16_t pc; // Program Counter
        union
        {
            uint8_t p;
            struct
            {
                uint8_t c : 1; // Carry (bit 0)
                uint8_t z : 1; // Zero (bit 1)
                uint8_t i : 1; // Interrupt-Disable (bit 2)
                uint8_t d : 1; // Decimal (bit 3)
                uint8_t b : 1; // Break (bit 4)
                uint8_t _ : 1; // Padding (bit 5)
                uint8_t v : 1; // Overflow (bit 6)
                uint8_t n : 1; // Negative (bit 7)
            };
        }; // Status

        // instruction translate_opcode();
        uint64_t cycles = 0;

    private:
        void increment_pc(uint8_t n = 1);
        uint8_t read_byte(uint16_t address);
        void write_byte(uint16_t address, uint8_t byte);

        uint8_t fetch_pc_byte();
        uint16_t fetch_pc_word();

        uint16_t read_word(uint16_t address);
        void write_word(uint16_t address, uint16_t word);

        struct Operation
        {
            std::string instruction;
            std::string addressMode;
        };

        Operation decode(uint8_t opcode);
        Operation lookup_by_parser(uint8_t opcode);
    };
} // namespace component
