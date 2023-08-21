#pragma once

#include <ostream>
#include <string_view>

#include <src/components/interface.h>

namespace application
{
    class OStreamLogger : public components::Logger
    {
    public:
        OStreamLogger(std::ostream &out);
        void log(std::string_view message);

    private:
        std::ostream &out_;
    };
} // namespace application
