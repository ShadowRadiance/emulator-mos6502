#pragma once

#include "_base.h"

#include <src/components/interface.h>

namespace components {
  namespace operations {
    class BRK : public Base
    {
    public:
      BRK(CPU &cpu, Logger &logger);

      void execute() override;
    };
  } // namespace operations

} // namespace components
