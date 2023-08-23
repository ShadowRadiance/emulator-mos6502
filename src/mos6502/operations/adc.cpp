#include "./adc.h"

#include <src/components/address_modes.h>
#include <typeinfo>

namespace components {
  namespace operations {
    ADC::ADC(CPU &cpu, Logger &logger, AddressMode &mode) : Base(cpu, logger, mode) {}

    void ADC::execute() {
      logger().log(name());
      return;
    }
  } // namespace operations

} // namespace components
