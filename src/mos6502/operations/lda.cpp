#include "lda.h"

#include <format>
#include <src/mos6502/addressing/modes.h>
#include <stdexcept>
#include <typeinfo>

namespace mos6502 {
  namespace operations {
    LDA::LDA(mos6502::CPU &cpu, emulator::Logger &logger, std::string mode) : Base(cpu, logger, mode) {
      // if (!allowedModeTypeIdHashCodes().contains(typeid(mode).hash_code())) {
      //   throw std::invalid_argument("addressMode invalid");
      // }
    }

    std::string LDA::name() const {
      return "LDA";
    }
    void LDA::execute() {
      logger().log(std::format("{} {}", name(), mode()));
            // uint8_t value = mode().resolve_value(cpu());

            // cpu().a = value;
            // cpu().setNegativeBit(value >> 7 & 1);
            // cpu().setZeroBit(value == 0 ? 1 : 0);

      return;
    }

    // std::set<size_t> LDA::allowedModeTypeIdHashCodes() {
    //   return {
    //     {typeid(addressing::Absolute).hash_code()},
    //     {typeid(addressing::AbsoluteX).hash_code()},
    //     {typeid(addressing::AbsoluteY).hash_code()},
    //     {typeid(addressing::Immediate).hash_code()},
    //     {typeid(addressing::ZeroPage).hash_code()},
    //     {typeid(addressing::ZeroPageXIndirect).hash_code()},
    //     {typeid(addressing::ZeroPageX).hash_code()},
    //     {typeid(addressing::ZeroPageIndirectY).hash_code()},
    //   };
    // }

  } // namespace operations

} // namespace mos6502
