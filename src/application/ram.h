#pragma once

#include <array>
#include <cstdint>

namespace application {
  class RAM
  {
  public:
    void clear();
    const uint8_t &operator[](uint16_t index) const;
    uint8_t &operator[](uint16_t index);

  private:
    std::array<uint8_t, 65'536> data; // 2^16
  };
} // namespace application
