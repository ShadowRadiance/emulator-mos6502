#include "_base.h"

#include <format>
#include <src/mos6502/addressing/modes.h>
#include <typeinfo>

namespace mos6502 {
  namespace operations {
    Base::Base(mos6502::CPU &cpu, emulator::Logger &logger, std::string mode)
            : cpu_(cpu)
            , logger_(logger)
            , mode_(mode) {}

    CPU &Base::cpu() const {
      return cpu_;
    }

    emulator::Logger &Base::logger() const {
      return logger_;
    }

    std::string Base::mode() const {
      return mode_;
    }

    std::set<size_t> Base::allowedModeTypeIdHashCodes() {
      return {};
    }

    std::set<size_t> Base::allModeTypeIdHashCodes() {
      return {
        {typeid(addressing::Absolute).hash_code()},
        {typeid(addressing::AbsoluteIndirect).hash_code()},
        {typeid(addressing::AbsoluteX).hash_code()},
        {typeid(addressing::AbsoluteY).hash_code()},
        {typeid(addressing::Accumulator).hash_code()},
        {typeid(addressing::Immediate).hash_code()},
        {typeid(addressing::Implied).hash_code()},
        {typeid(addressing::Relative).hash_code()},
        {typeid(addressing::ZeroPage).hash_code()},
        {typeid(addressing::ZeroPageIndirectY).hash_code()},
        {typeid(addressing::ZeroPageX).hash_code()},
        {typeid(addressing::ZeroPageXIndirect).hash_code()},
        {typeid(addressing::ZeroPageY).hash_code()},
      };
    }

  }// namespace operations
}// namespace mos6502
