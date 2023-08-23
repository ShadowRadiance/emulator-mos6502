#include "adc.h"

#include <format>
#include <src/mos6502/addressing/modes.h>
#include <typeinfo>

namespace mos6502 {
  namespace operations {
    ADC::ADC(mos6502::CPU &cpu, emulator::Logger &logger, std::string mode) : Base(cpu, logger, mode) {}

    std::string ADC::name() const {
      return "ADC";
    }

    void ADC::execute() {
      logger().log(std::format("{} {}", name(), mode()));
      return;
    }
  } // namespace operations

} // namespace mos6502
