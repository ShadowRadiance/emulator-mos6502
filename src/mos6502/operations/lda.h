#pragma once

#include "_base.h"

#include <src/emulator/logger.h>
#include <src/mos6502/cpu.h>

namespace mos6502 {
  namespace operations {
    class LDA : public Base
    {
    public:
      LDA(mos6502::CPU &cpu, emulator::Logger &logger, std::string mode);

      std::string name() const;
      void execute() override;
      // std::set<size_t> allowedModeTypeIdHashCodes() override;
    };
  } // namespace operations

} // namespace mos6502
