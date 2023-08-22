#pragma once

#include <set>
#include <string>
#include <src/components/interface.h>

namespace components
{
    namespace operations
    {
        class Base : public Operation
        {
        public:
            Base(CPU &cpu, Logger &logger, AddressMode &mode);
            std::string name() const override;

        protected:
            CPU &cpu() const;
            Logger &logger() const;
            AddressMode &mode() const;

            virtual std::set<size_t> allowedModeTypeIdHashCodes();
            std::set<size_t> allModeTypeIdHashCodes();

        private:
            CPU &cpu_;
            Logger &logger_;
            AddressMode &mode_;
        };
    } // namespace operations

} // namespace components
