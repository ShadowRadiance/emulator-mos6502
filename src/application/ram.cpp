#include "ram.h"

namespace application {
  void RAM::clear() {
    data.fill(0);
  }

  const uint8_t &RAM::operator[](uint16_t index) const {
    return data[index];
  }

  uint8_t &RAM::operator[](uint16_t index) {
    return data[index];
  }

} // namespace application
