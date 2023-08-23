#include "./asl.h"

#include <src/components/address_modes.h>
#include <stdexcept>
#include <typeinfo>

namespace components {
  namespace operations {
    ASL::ASL(CPU &cpu, Logger &logger, AddressMode &mode) : Base(cpu, logger, mode) {
      if (!allowedModeTypeIdHashCodes().contains(typeid(mode).hash_code())) {
        throw std::invalid_argument("addressMode invalid");
      }
    }

    std::set<size_t> ASL::allowedModeTypeIdHashCodes() {
      return {
        {typeid(addressing::Absolute).hash_code()},
        {typeid(addressing::AbsoluteX).hash_code()},
        {typeid(addressing::Accumulator).hash_code()},
        {typeid(addressing::ZeroPage).hash_code()},
        {typeid(addressing::ZeroPageX).hash_code()},
      };
    }

    void ASL::execute() {
      logger().log(name());
      return;
    }
  } // namespace operations

} // namespace components
