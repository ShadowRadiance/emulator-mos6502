#pragma once

#include <src/application/ram.h>

namespace compsystem {
  class Test
  {
  public:
    Test(application::RAM &ram);

  private:
    application::RAM &ram_;
  };
} // namespace compsystem
