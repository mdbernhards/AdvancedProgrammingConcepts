//
// Created by dza02 on 8/25/2021.
//

#ifndef LESSON_ILOGGER_H
#define LESSON_ILOGGER_H

#include <string_view>

namespace loggers {
    class ilogger {
    public:
        virtual void log(std::string_view msg) const = 0;
        virtual ~ilogger() noexcept = default;
    };
}


#endif //LESSON_ILOGGER_H
