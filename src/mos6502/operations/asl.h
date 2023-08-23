#pragma once

#include "_base.h"

#include <src/components/interface.h>

namespace components {
  namespace operations {
    class ASL : public Base
    {
    public:
      ASL(CPU &cpu, Logger &logger, AddressMode &mode);

      void execute() override;
      std::set<size_t> allowedModeTypeIdHashCodes() override;
    };
  } // namespace operations

} // namespace components