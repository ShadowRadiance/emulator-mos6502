#pragma once

#include <cstdint>
#include <string>
#include <string_view>

namespace emulator {
  struct Memory
  {
    virtual const uint8_t &operator[](uint16_t index) const = 0;
    virtual uint8_t &operator[](uint16_t index) = 0;
  };

  struct WritableMemory : public Memory
  {
    virtual void clear() = 0;
  };
}// namespace emulator
