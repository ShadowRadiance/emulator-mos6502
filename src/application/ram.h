#pragma once

#include <src/interface/memory.h>
#include <array>

namespace application
{
    class RAM : public emulator::WritableMemory
    {
    public:
        void clear() override;
        const uint8_t &operator[](uint16_t index) const override;
        uint8_t &operator[](uint16_t index) override;

    private:
        std::array<uint8_t, 65536> data; // 2^16
    };
} // namespace component
