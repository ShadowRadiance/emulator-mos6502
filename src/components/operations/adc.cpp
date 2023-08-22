#include "./adc.h"

namespace components
{
    namespace operations
    {
        ADC::ADC(Logger &logger, AddressMode &mode) : logger_(logger), mode_(mode) {}

        void ADC::execute()
        {
            logger_.log("ADC");
            return;
        }
    } // namespace operations

} // namespace components
