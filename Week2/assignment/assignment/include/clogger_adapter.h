#ifndef LESSON_CloggerAdapter_H
#define LESSON_CloggerAdapter_H

#include <chrono>
#include <stdexcept>
#include <string_view>
#include "ilogger.h"
#include "../clib/logger.h"

namespace lib
{
    class clogger_adapter: public loggers::ilogger 
    {
        public:
            clogger_adapter(std::chrono::seconds roll_interval);
            ~clogger_adapter();
            
            void log(std::string_view msg) const override;
        private:
            lg_logger_t* m_clogger = NULL; 
    };

}

#endif //LESSON_CloggerAdapter_H