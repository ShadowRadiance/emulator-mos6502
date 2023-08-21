#include "./ostream_logger.h"

namespace application
{
    OStreamLogger::OStreamLogger(std::ostream &out)
        : out_(out)
    {
    }

    void OStreamLogger::log(std::string_view message)
    {
        out_ << message << "\n";
    }
} // namespace application
