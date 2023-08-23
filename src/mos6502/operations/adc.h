#pragma once

#include "_base.h"

#include <src/components/interface.h>

namespace components {
  namespace operations {
    class ADC : public Base
    {
    public:
      ADC(CPU &cpu, Logger &logger, AddressMode &mode);

      void execute() override;
    };
  } // namespace operations

} // namespace components
