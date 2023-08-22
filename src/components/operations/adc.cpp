#include "./adc.h"

#include <typeinfo>
#include <src/components/address_modes.h>

namespace components
{
    namespace operations
    {
        ADC::ADC(CPU &cpu, Logger &logger, AddressMode &mode) : Base(cpu, logger, mode)
        {
        }

        void ADC::execute()
        {
            logger().log("ADC");
            return;
        }
    } // namespace operations

} // namespace components
