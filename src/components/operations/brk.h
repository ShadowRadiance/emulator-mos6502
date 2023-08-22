#pragma once

#include <src/components/interface.h>

namespace components
{
    namespace operations
    {
        class BRK : public Operation
        {
        public:
            BRK(Logger &logger);

            void execute();

        private:
            Logger &logger_;
        };
    } // namespace operations

} // namespace components
