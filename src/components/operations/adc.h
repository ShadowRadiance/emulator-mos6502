#pragma once

#include <src/components/interface.h>
#include "_base.h"

namespace components
{
    namespace operations
    {
        class ADC : public Base
        {
        public:
            ADC(CPU &cpu, Logger &logger, AddressMode &mode);

            void execute() override;
        };
    } // namespace operations

} // namespace components
