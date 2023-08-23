#pragma once

#include "_base.h"

#include <src/components/interface.h>

namespace components {
  namespace operations {
    class LDA : public Base
    {
    public:
      LDA(CPU &cpu, Logger &logger, AddressMode &mode);

      void execute() override;
      std::set<size_t> allowedModeTypeIdHashCodes() override;
    };
  } // namespace operations

} // namespace components
