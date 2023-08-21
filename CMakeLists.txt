cmake_minimum_required(VERSION 3.27.0)
project(Emu6502 VERSION 1.0)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(Emu6502 src/main.cpp 
    src/application/ostream_logger.cpp
    src/components/mos6502.cpp
    src/components/writable_memory.cpp
    src/components/opcode_parser.cpp
    src/components/addressing/absolute_indirect.cpp
    src/components/addressing/absolute_x.cpp
    src/components/addressing/absolute_y.cpp
    src/components/addressing/absolute.cpp
    src/components/addressing/accumulator.cpp
    src/components/addressing/immediate.cpp
    src/components/addressing/implied.cpp
    src/components/addressing/relative.cpp
    src/components/addressing/zero_page_indirect_y.cpp
    src/components/addressing/zero_page_x_indirect.cpp
    src/components/addressing/zero_page_x.cpp
    src/components/addressing/zero_page_y.cpp
    src/components/addressing/zero_page.cpp
    )

configure_file(src/version.h.in version.h)
target_include_directories(Emu6502 
    PUBLIC ${PROJECT_BINARY_DIR}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
