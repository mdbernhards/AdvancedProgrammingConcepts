
#ifndef LESSON_SYSTEMTIMESOURCE_H
#define LESSON_SYSTEMTIMESOURCE_H

#include <string>
#include <iostream>
#include <memory>
#include "itime_source.h"
#include "ilogger.h"

namespace time_source
{
    class system_time_source: public itime_source 
    {
        public:
            std::string_view output_time() const override;
        private:
            std::unique_ptr<lib::ilogger> m_logger;
    };
}

#endif //LESSON_SYSTEMTIMESOURCE_H