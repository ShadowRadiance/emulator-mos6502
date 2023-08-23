#include <iostream>
#include <src/application/ostream_logger.h>
#include <src/application/ram.h>
#include <src/mos6502/cpu.h>

int main(int argc, char const *argv[]) {
  application::OStreamLogger logger(std::cout);
  application::RAM ram;
  mos6502::CPU cpu(ram, logger);

  ram[0x0000] = 0xA9; // LDA #
  ram[0x0001] = 0x42; // LDA #$42

  while (cpu.tick()) /* nop */
    ;

  return 0;
}
