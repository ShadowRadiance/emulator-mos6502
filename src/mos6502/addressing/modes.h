#pragma once

#include <string>
#include <cstdint>

namespace mos6502
{
    namespace addressing
    {
        class AbsoluteIndirect
        {
            std::string name() const;
            std::string code() const;
            uint16_t resolve_address() const;
            uint8_t resolve_value() const;
        };
        class AbsoluteX
        {
            std::string name() const;
            std::string code() const;
            uint16_t resolve_address() const;
            uint8_t resolve_value() const;
        };
        class AbsoluteY
        {
            std::string name() const;
            std::string code() const;
            uint16_t resolve_address() const;
            uint8_t resolve_value() const;
        };
        class Absolute
        {
            std::string name() const;
            std::string code() const;
            uint16_t resolve_address() const;
            uint8_t resolve_value() const;
        };
        class Accumulator
        {
            std::string name() const;
            std::string code() const;
            uint16_t resolve_address() const;
            uint8_t resolve_value() const;
        };
        class Immediate
        {
            std::string name() const;
            std::string code() const;
            uint16_t resolve_address() const;
            uint8_t resolve_value() const;
        };
        class Implied
        {
            std::string name() const;
            std::string code() const;
            uint16_t resolve_address() const;
            uint8_t resolve_value() const;
        };
        class Relative
        {
            std::string name() const;
            std::string code() const;
            uint16_t resolve_address() const;
            uint8_t resolve_value() const;
        };
        class ZeroPageIndirectY
        {
            std::string name() const;
            std::string code() const;
            uint16_t resolve_address() const;
            uint8_t resolve_value() const;
        };
        class ZeroPageXIndirect
        {
            std::string name() const;
            std::string code() const;
            uint16_t resolve_address() const;
            uint8_t resolve_value() const;
        };
        class ZeroPageX
        {
            std::string name() const;
            std::string code() const;
            uint16_t resolve_address() const;
            uint8_t resolve_value() const;
        };
        class ZeroPageY
        {
            std::string name() const;
            std::string code() const;
            uint16_t resolve_address() const;
            uint8_t resolve_value() const;
        };
        class ZeroPage
        {
            std::string name() const;
            std::string code() const;
            uint16_t resolve_address() const;
            uint8_t resolve_value() const;
        };
    }
}
