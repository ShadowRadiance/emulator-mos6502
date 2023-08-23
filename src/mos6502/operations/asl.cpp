#include "asl.h"

#include <format>
#include <src/mos6502/addressing/modes.h>
#include <stdexcept>
#include <typeinfo>

namespace mos6502 {
  namespace operations {
    ASL::ASL(mos6502::CPU &cpu, emulator::Logger &logger, std::string mode) : Base(cpu, logger, mode) {
      // if (!allowedModeTypeIdHashCodes().contains(typeid(mode).hash_code())) {
      //   throw std::invalid_argument("addressMode invalid");
      // }
    }

    // std::set<size_t> ASL::allowedModeTypeIdHashCodes() {
    //   return {
    //     {typeid(addressing::Absolute).hash_code()},
    //     {typeid(addressing::AbsoluteX).hash_code()},
    //     {typeid(addressing::Accumulator).hash_code()},
    //     {typeid(addressing::ZeroPage).hash_code()},
    //     {typeid(addressing::ZeroPageX).hash_code()},
    //   };
    // }

    std::string ASL::name() const {
      return "ASL";
    }
    void ASL::execute() {
      logger().log(std::format("{} {}", name(), mode()));
      return;
    }
  } // namespace operations

} // namespace mos6502
