#include "test.h"

namespace compsystem {
  Test::Test(application::RAM &ram) : ram_(ram) {
    ram_[0x0000] = 0xA9; // LDA #$42   #       A = $42
    ram_[0x0001] = 0x42;
    ram_[0x0002] = 0xA6; // LDX $42    zp      X = $02
    ram_[0x0003] = 0x42;
    ram_[0x0004] = 0xB5; // LDA $42,X  zp,x    A = $99
    ram_[0x0005] = 0x42;
    ram_[0x0006] = 0xAD; // LDA $4400  a       A = $16
    ram_[0x0007] = 0x00;
    ram_[0x0008] = 0x44;
    ram_[0x0009] = 0x00;

    ram_[0x0042] = 0x02;
    ram_[0x0043] = 0x00;
    ram_[0x0044] = 0x99;
    ram_[0x4400] = 0x16;

    ram_[0xFFFC] = 0x00;
    ram_[0xFFFD] = 0x00;
  }
}// namespace compsystem
