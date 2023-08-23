#pragma once

namespace emulator {
  struct CPU
  {
    virtual void reset() = 0;
    virtual bool tick() = 0;
  };
}// namespace emulator
