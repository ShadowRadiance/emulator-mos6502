#include <iostream>

#include <src/components/interface.h>

#include <src/application/ostream_logger.h>
#include <src/components/mos6502.h>
#include <src/components/writable_memory.h>

int main(int argc, char const *argv[])
{
    application::OStreamLogger logger(std::cout);
    components::WritableMemory ram;
    components::MOS6502 cpu(ram, logger);

    ram[0x0000] = 0xA9; // LDA #
    ram[0x0001] = 0x42; // LDA #$42

    while (cpu.tick())
        /* nop */;

    return 0;
}
