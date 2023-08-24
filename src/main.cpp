#include <iostream>
#include <src/application/logger.h>
#include <src/application/ram.h>
#include <src/mos6502/cpu.h>
#include <src/system/test.h>

int main(int argc, char const *argv[]) {
  application::Logger logger(std::cout);
  application::RAM ram;

  // compsystem::NES nes(ram);
  // compsystem::Electron nes(ram);
  // compsystem::BBC nes(ram);
  compsystem::Test test(ram);

  mos6502::CPU cpu(ram, logger);
  while (cpu.tick()) {
  }

  return 0;
}
