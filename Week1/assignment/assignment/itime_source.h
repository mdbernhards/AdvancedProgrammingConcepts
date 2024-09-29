#ifndef LESSON_ITIMESOURCE_H
#define LESSON_ITIMESOURCE_H

#include <string_view>

namespace time_source
{
    class itime_source 
    {
        public:
            virtual std::string_view output_time() const = 0;
            virtual ~itime_source() = default;
    };
}

#endif //LESSON_ILOGGER_H