#include <ctime>
#include "system_time_source.h"

namespace time_source
{
    std::string_view system_time_source::output_time() const 
    {
        auto time_point = std::time(nullptr);
        auto local_time = std::localtime(&time_point);
        char buffer[16];
        std::strftime(&buffer[0], sizeof(buffer),"%I:%M:%S", local_time);
        return buffer;
    }
}