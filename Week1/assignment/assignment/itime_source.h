#ifndef LESSON_ILOGGER_H
#define LESSON_ILOGGER_H

#include <string>

namespace time_source {
    class itime_source {
    public:
        virtual void getTimeStamp(const std::string& msg) const = 0;

        // Always provide a virtual destructor when a class has a virtual fucntion
        virtual ~itime_source() = default;
    };
}


#endif //LESSON_ILOGGER_H