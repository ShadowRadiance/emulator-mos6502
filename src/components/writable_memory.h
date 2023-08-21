#pragma once

#include <cstdint>

#include <array>
#include <src/components/interface.h>

namespace components
{
    class WritableMemory : public RandomAccessMemory
    {
    public:
        void clear();
        const uint8_t &operator[](uint16_t index) const;
        uint8_t &operator[](uint16_t index);

    private:
        std::array<uint8_t, 65536> data; // 2^16
    };
} // namespace component
