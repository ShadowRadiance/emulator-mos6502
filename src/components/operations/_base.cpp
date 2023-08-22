#include "./_base.h"

#include <typeinfo>
#include <src/components/address_modes.h>

namespace components
{
    namespace operations
    {
        Base::Base(CPU &cpu, Logger &logger, AddressMode &mode)
            : cpu_(cpu), logger_(logger), mode_(mode) {}

        CPU &Base::cpu() { return cpu_; }
        Logger &Base::logger() { return logger_; }
        AddressMode &Base::mode() { return mode_; }

        std::set<size_t> Base::allowedModeTypeIdHashCodes()
        {
            return {};
        }

        std::set<size_t> Base::allModeTypeIdHashCodes()
        {
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

    }
}