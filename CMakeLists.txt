cmake_minimum_required(VERSION 3.27.0)
project(Emu6502 VERSION 1.0)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(Emu6502 src/main.cpp 
    src/application/logger.cpp
    src/application/ram.cpp
    src/mos6502/cpu.cpp
    src/mos6502/opcode_table.cpp
    src/mos6502/operation.cpp
    src/mos6502/instruction.cpp
    src/mos6502/address_mode.cpp
    
    src/system/test.cpp
    # src/system/bbc.cpp
    # src/system/electron.cpp
    # src/system/nes.cpp
)

configure_file(src/version.h.in version.h)
target_include_directories(Emu6502 
    PUBLIC ${PROJECT_BINARY_DIR}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
