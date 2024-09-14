#include <ctime>
#include "system_time_source.h"

namespace item_source
{
    std::string_view item_source::output_time() {
        auto time_point = std::time(nullptr);
        auto local_time = std::localtime(&time_point);
        char buffer[16];
        std::strftime(&buffer[0], sizeof(buffer),"%H:%M:%S", local_time);
        return buffer;
    }
}