#include <iostream>
#include <src/application/logger.h>
#include <src/application/ram.h>
#include <src/mos6502/cpu.h>

int main(int argc, char const *argv[]) {
  application::Logger logger(std::cout);
  application::RAM ram;
  mos6502::CPU cpu(ram, logger);

  ram[0x0000] = 0xA9; // LDA #$42   #       A = $42
  ram[0x0001] = 0x42;
  ram[0x0002] = 0xA6; // LDX $42    zp      X = $02
  ram[0x0003] = 0x42;
  ram[0x0004] = 0xB5; // LDA $42,X  zp,x    A = $99
  ram[0x0005] = 0x42;
  ram[0x0006] = 0xAD; // LDA $4400  a       A = $16
  ram[0x0007] = 0x00;
  ram[0x0008] = 0x44;
  ram[0x0009] = 0x00;
  //...
  ram[0x0042] = 0x02;
  ram[0x0043] = 0x00;
  ram[0x0044] = 0x99;
  //...
  ram[0x4400] = 0x16;

  while (cpu.tick()) {
  }

  return 0;
}
