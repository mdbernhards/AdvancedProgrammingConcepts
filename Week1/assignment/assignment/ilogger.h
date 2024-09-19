//
// Created by Dawid Zalewski on 8/25/2021.
//

#ifndef LESSON_ILOGGER_H
#define LESSON_ILOGGER_H

namespace lib 
{
    class ilogger 
    {
        public:
            virtual void log(const std::string_view& msg) const = 0;
            virtual ~ilogger() = default;
    };
}

#endif //LESSON_ILOGGER_H
