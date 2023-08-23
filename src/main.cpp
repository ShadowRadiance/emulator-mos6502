#include <iostream>
#include <src/application/logger.h>
#include <src/application/ram.h>
#include <src/mos6502/cpu.h>

int main(int argc, char const *argv[]) {
  application::Logger logger(std::cout);
  application::RAM ram;
  mos6502::CPU cpu(ram, logger);

  ram[0x0000] = 0xA9; // LDA #$42
  ram[0x0001] = 0x42;

  while (cpu.tick()) /* nop */
    ;

  return 0;
}
