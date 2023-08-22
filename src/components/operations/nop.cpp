#include "./nop.h"

namespace components
{
    namespace operations
    {
        NOP::NOP(Logger &logger) : logger_(logger) {}

        void NOP::execute()
        {
            logger_.log("NOP");
            return;
        }
    } // namespace operations

} // namespace components
