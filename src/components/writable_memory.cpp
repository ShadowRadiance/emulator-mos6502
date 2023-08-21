#include "./writable_memory.h"

namespace components
{
    void WritableMemory::clear()
    {
        data.fill(0);
    }

    const uint8_t &WritableMemory::operator[](uint16_t index) const
    {
        return data[index];
    }

    uint8_t &WritableMemory::operator[](uint16_t index)
    {
        return data[index];
    }

} // namespace component
