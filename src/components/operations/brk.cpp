#include "./brk.h"

namespace components
{
    namespace operations
    {
        BRK::BRK(CPU &cpu, Logger &logger) : logger_(logger) {}

        void BRK::execute()
        {
            logger_.log("BRK");
            return;
        }
    } // namespace operations

} // namespace components
