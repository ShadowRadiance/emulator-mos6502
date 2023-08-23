#pragma once

#include "_base.h"

#include <src/components/interface.h>

namespace components {
  namespace operations {
    class NOP : public Base
    {
    public:
      NOP(CPU &cpu, Logger &logger);

      void execute() override;
    };
  } // namespace operations

} // namespace components
