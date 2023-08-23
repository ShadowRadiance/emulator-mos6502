#pragma once

#include "_base.h"

#include <src/emulator/logger.h>
#include <src/mos6502/cpu.h>

namespace mos6502 {
  namespace operations {
    class BRK : public Base
    {
    public:
      BRK(mos6502::CPU &cpu, emulator::Logger &logger);

      std::string name() const;
      void execute() override;
    };
  } // namespace operations

} // namespace mos6502
