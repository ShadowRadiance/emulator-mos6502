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

    while (cpu.tick())
        /* nop */;

    return 0;
}