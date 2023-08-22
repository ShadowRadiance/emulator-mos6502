#include "./brk.h"

#include <typeinfo>
#include <src/components/address_modes.h>
#include <src/components/mos6502.h>

namespace components
{
    namespace operations
    {
        BRK::BRK(CPU &cpu, Logger &logger) : Base(cpu, logger, *MOS6502::addressModes["i"]) {}

        void BRK::execute()
        {
            logger().log(name());
            return;
        }
    } // namespace operations

} // namespace components
