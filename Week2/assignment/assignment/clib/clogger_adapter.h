#ifndef LESSON_CloggerAdapter_H
#define LESSON_CloggerAdapter_H

#include "ilogger.h";

namespace lib
{
    class clogger_adapter: public loggers::ilogger 
    {
        public:
            void log(std::string_view msg) override;
            lib::clogger_adapter::clogger_adapter(std::chrono::seconds roll_interval);
        private:
        
    }

}


#endif //LESSON_CloggerAdapter_H