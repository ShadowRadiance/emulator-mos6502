#pragma once

#include <src/components/interface.h>

namespace components
{
    namespace operations
    {
        class ASL : public Operation
        {
        public:
            ASL(Logger &logger);

            void execute();

        private:
            Logger &logger_;
        };
    } // namespace operations

} // namespace components
