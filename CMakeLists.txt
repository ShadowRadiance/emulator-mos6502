cmake_minimum_required(VERSION 3.27.0)
project(Emu6502 VERSION 1.0)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB AddressModes src/mos6502/addressing/*.cpp)
file(GLOB Operations src/mos6502/operations/*.cpp)

add_executable(Emu6502 src/main.cpp 
    src/application/ostream_logger.cpp
    src/application/ram.cpp
    src/mos6502/cpu.cpp
    src/mos6502/mos6502_opcode_decoder.cpp
    ${AddressModes}
    ${Operations}
)

configure_file(src/version.h.in version.h)
target_include_directories(Emu6502 
    PUBLIC ${PROJECT_BINARY_DIR}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
