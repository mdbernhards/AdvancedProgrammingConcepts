
#ifndef LESSON_SYSTEMTIMESOURCE_H
#define LESSON_SYSTEMTIMESOURCE_H

#include <string>
#include <iostream>
#include <memory>
#include "itime_source.h"

namespace item_source{
class system_time_source: public lib::itime_source {
    public:
        std::string_view output_time() const override;
    private:
        std::ostream& m_out;
        std::unique_ptr<loggers::ilogger> m_logger;
    };
}

#endif //LESSON_ILOGGER_H