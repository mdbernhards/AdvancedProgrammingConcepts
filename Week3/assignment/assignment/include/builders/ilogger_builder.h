//
// Created by dza02 on 9/6/2021.
//

#ifndef LESSON_ILOGGER_BUILDER_H
#define LESSON_ILOGGER_BUILDER_H

#include <string_view>
#include <memory>
#include <chrono>
#include "ilogger.h"

namespace io {
    class itext_writer;
}

namespace builders {

    class ilogger_builder {
    public:
        enum class timestamp_type { none, current_time, running_time };

        virtual ilogger_builder& reset() = 0;

        virtual ilogger_builder& with_console_output() = 0;
        virtual ilogger_builder& with_file_output(std::string_view file_name) = 0;
        virtual std::unique_ptr<loggers::ilogger> get() = 0;

        virtual ~ilogger_builder() = default;
        
        virtual ilogger_builder& with_writer(std::unique_ptr<io::itext_writer> writer) = 0;
        virtual ilogger_builder& with_timestamp(timestamp_type type) = 0;
        virtual ilogger_builder& with_rolling_log_with_interval(std::chrono::seconds interval) = 0;
    };
}


#endif //LESSON_ILOGGER_BUILDER_H
