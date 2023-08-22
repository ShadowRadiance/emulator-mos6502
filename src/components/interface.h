#pragma once

#include <cstdint>
#include <string_view>
#include <string>

namespace components
{
    struct Logger
    {
        virtual void log(std::string_view message) = 0;
    };

    struct RandomAccessMemory
    {
        virtual void clear() = 0;
        virtual const uint8_t &operator[](uint16_t index) const = 0;
        virtual uint8_t &operator[](uint16_t index) = 0;
    };

    struct CPU
    {
        virtual void reset() = 0;
        virtual bool tick() = 0;
    };

    struct AddressMode
    {
        virtual std::string name() const = 0;
        virtual std::string code() const = 0;
        virtual uint16_t resolve_address() const = 0;
        virtual uint8_t resolve_value() const = 0;
    };

    struct Operation
    {
        virtual std::string name() const = 0;
        virtual void execute() = 0;
        virtual ~Operation() = default;
    };

}
