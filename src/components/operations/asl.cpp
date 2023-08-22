#include "./asl.h"

#include <typeinfo>
#include <src/components/address_modes.h>
#include <stdexcept>
#include <format>

namespace components
{
    namespace operations
    {
        ASL::ASL(CPU &cpu, Logger &logger, AddressMode &addressMode) : Base(cpu, logger, addressMode)
        {
            if (!allowedModeTypeIdHashCodes().contains(typeid(addressMode).hash_code()))
            {
                throw std::invalid_argument("addressMode invalid");
            }
        }

        std::set<size_t> ASL::allowedModeTypeIdHashCodes()
        {
            return {
                {typeid(addressing::Absolute).hash_code()},
                {typeid(addressing::AbsoluteX).hash_code()},
                {typeid(addressing::Accumulator).hash_code()},
                {typeid(addressing::ZeroPage).hash_code()},
                {typeid(addressing::ZeroPageX).hash_code()},
            };
        }

        void ASL::execute()
        {
            logger().log(name());
            return;
        }
    } // namespace operations

} // namespace components
