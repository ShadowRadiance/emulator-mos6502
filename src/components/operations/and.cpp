#include "./and.h"

#include <typeinfo>
#include <src/components/address_modes.h>

namespace components
{
    namespace operations
    {
        AND::AND(CPU &cpu, Logger &logger, AddressMode &mode) : Base(cpu, logger, mode) {}

        void AND::execute()
        {
            logger().log(name());
            return;
        }
    } // namespace operations

} // namespace components
