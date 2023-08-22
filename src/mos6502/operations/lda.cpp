#include "./lda.h"

#include <typeinfo>
#include <src/components/address_modes.h>
#include <stdexcept>

namespace components
{
    namespace operations
    {
        LDA::LDA(CPU &cpu, Logger &logger, AddressMode &mode) : Base(cpu, logger, mode)
        {
            if (!allowedModeTypeIdHashCodes().contains(typeid(mode).hash_code()))
            {
                throw std::invalid_argument("addressMode invalid");
            }
        }

        void LDA::execute()
        {
            logger().log(name());
            // uint8_t value = mode().resolve_value(cpu());

            // cpu().a = value;
            // cpu().setNegativeBit(value >> 7 & 1);
            // cpu().setZeroBit(value == 0 ? 1 : 0);

            return;
        }

        std::set<size_t> LDA::allowedModeTypeIdHashCodes()
        {
            return {
                {typeid(addressing::Absolute).hash_code()},
                {typeid(addressing::AbsoluteX).hash_code()},
                {typeid(addressing::AbsoluteY).hash_code()},
                {typeid(addressing::Immediate).hash_code()},
                {typeid(addressing::ZeroPage).hash_code()},
                {typeid(addressing::ZeroPageXIndirect).hash_code()},
                {typeid(addressing::ZeroPageX).hash_code()},
                {typeid(addressing::ZeroPageIndirectY).hash_code()},
            };
        }

    } // namespace operations

} // namespace components
