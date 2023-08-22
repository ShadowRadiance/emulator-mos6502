#pragma once

#include <src/components/interface.h>

namespace components
{
    namespace operations
    {
        class ADC : public Operation
        {
        public:
            ADC(Logger &logger, AddressMode &mode);

            void execute();

        private:
            Logger &logger_;
            AddressMode &mode_;
        };
    } // namespace operations

} // namespace components
