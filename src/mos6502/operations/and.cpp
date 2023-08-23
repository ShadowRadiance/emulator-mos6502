#include "./and.h"

#include <src/components/address_modes.h>
#include <typeinfo>

namespace components {
  namespace operations {
    AND::AND(CPU &cpu, Logger &logger, AddressMode &mode) : Base(cpu, logger, mode) {}

    void AND::execute() {
      logger().log(name());
      return;
    }
  } // namespace operations

} // namespace components
