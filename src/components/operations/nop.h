#pragma once

#include <src/components/interface.h>

namespace components
{
    namespace operations
    {
        class NOP : public Operation
        {
        public:
            NOP(Logger &logger);

            void execute();

        private:
            Logger &logger_;
        };
    } // namespace operations

} // namespace components
