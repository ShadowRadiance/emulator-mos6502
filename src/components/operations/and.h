#pragma once

#include <src/components/interface.h>

namespace components
{
    namespace operations
    {
        class AND : public Operation
        {
        public:
            AND(Logger &logger);

            void execute();

        private:
            Logger &logger_;
        };
    } // namespace operations

} // namespace components
