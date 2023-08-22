#pragma once

#include <src/components/interface.h>
#include "_base.h"

namespace components
{
    namespace operations
    {
        class ASL : public Base
        {
        public:
            ASL(CPU &cpu, Logger &logger, AddressMode &addressMode);

            void execute() override;
            std::set<size_t> allowedModeTypeIdHashCodes() override;
        };
    } // namespace operations

} // namespace components
