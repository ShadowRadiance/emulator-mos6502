#pragma once

#include <set>
#include <string>
#include <src/components/interface.h>
#include <src/components/mos6502.h>

namespace mos6502
{
    namespace operations
    {
        class Base
        {
        public:
            Base(MOS6502 &cpu, Logger &logger, AddressMode &mode);
            std::string name() const;
            virtual void execute() = 0;
            virtual ~Base() = default;

        protected:
            MOS6502 &cpu() const;
            Logger &logger() const;
            AddressMode &mode() const;

            virtual std::set<size_t> allowedModeTypeIdHashCodes();
            std::set<size_t> allModeTypeIdHashCodes();

        protected:
            MOS6502 &cpu_;
            Logger &logger_;
            AddressMode &mode_;
        };
    } // namespace operations

} // namespace components
