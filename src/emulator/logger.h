#pragma once

#include <string_view>

namespace emulator
{
    struct Logger
    {
        virtual void log(std::string_view message) = 0;
    };
}
