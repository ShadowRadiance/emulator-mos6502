#pragma once

#include <set>
#include <src/emulator/logger.h>
#include <src/mos6502/cpu.h>
#include <string>

namespace mos6502 {
  namespace operations {
    class Base
    {
    public:
      Base(mos6502::CPU &cpu, emulator::Logger &logger, std::string mode);
      virtual std::string name() const = 0;
      virtual void execute() = 0;
      virtual ~Base() = default;

    protected:
      mos6502::CPU &cpu() const;
      emulator::Logger &logger() const;
      std::string mode() const;

      virtual std::set<size_t> allowedModeTypeIdHashCodes();
      std::set<size_t> allModeTypeIdHashCodes();

    protected:
      mos6502::CPU &cpu_;
      emulator::Logger &logger_;
      std::string mode_;
    };
  } // namespace operations

} // namespace mos6502
