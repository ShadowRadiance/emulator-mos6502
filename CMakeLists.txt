cmake_minimum_required(VERSION 3.27.0)
project(Emu6502 VERSION 1.0)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB AddressModes src/components/addressing/*.cpp)
file(GLOB Operations src/components/operations/*.cpp)

add_executable(Emu6502 src/main.cpp 
    src/application/ostream_logger.cpp
    src/components/mos6502.cpp
    src/components/mos6502_opcode_decoder.cpp
    src/components/opcode_parser.cpp
    src/components/writable_memory.cpp
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
