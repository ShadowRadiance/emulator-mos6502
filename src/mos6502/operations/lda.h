#pragma once

#include <src/components/interface.h>
#include "_base.h"

namespace components
{
    namespace operations
    {
        class LDA : public Base
        {
        public:
            LDA(CPU &cpu, Logger &logger, AddressMode &mode);

            void execute() override;
            std::set<size_t> allowedModeTypeIdHashCodes() override;
        };
    } // namespace operations

} // namespace components
