#include "./and.h"

namespace components
{
    namespace operations
    {
        AND::AND(Logger &logger) : logger_(logger) {}

        void AND::execute()
        {
            logger_.log("AND");
            return;
        }
    } // namespace operations

} // namespace components