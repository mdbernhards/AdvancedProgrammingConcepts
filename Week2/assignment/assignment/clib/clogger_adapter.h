#ifndef LESSON_CloggerAdapter_H
#define LESSON_CloggerAdapter_H

#include <chrono>
#include <stdexcept>
#include <string_view>
#include "ilogger.h"

namespace lib
{
    class clogger_adapter: public loggers::ilogger 
    {
        public:
            void log(std::string_view msg) const override;
            clogger_adapter(std::chrono::seconds roll_interval);
            ~clogger_adapter();
    };

}


#endif //LESSON_CloggerAdapter_H