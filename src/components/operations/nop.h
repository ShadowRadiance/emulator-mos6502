#pragma once

#include <src/components/interface.h>

namespace components
{
    namespace operations
    {
        class NOP : public Operation
        {
        public:
            NOP(CPU &cpu, Logger &logger);

            void execute() override;

        private:
            Logger &logger_;
        };
    } // namespace operations

} // namespace components
