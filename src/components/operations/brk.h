#pragma once

#include <src/components/interface.h>

namespace components
{
    namespace operations
    {
        class BRK : public Operation
        {
        public:
            BRK(CPU& cpu, Logger &logger);

            void execute() override;

        private:
            Logger &logger_;
        };
    } // namespace operations

} // namespace components
