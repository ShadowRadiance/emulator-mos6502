#include "./asl.h"

namespace components
{
    namespace operations
    {
        ASL::ASL(Logger &logger) : logger_(logger) {}

        void ASL::execute()
        {
            logger_.log("ASL");
            return;
        }
    } // namespace operations

} // namespace components
