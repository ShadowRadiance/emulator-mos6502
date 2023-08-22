#pragma once

#include <src/components/interface.h>
#include "_base.h"

namespace components
{
    namespace operations
    {
        class NOP : public Base
        {
        public:
            NOP(CPU &cpu, Logger &logger);

            void execute() override;
        };
    } // namespace operations

} // namespace components
