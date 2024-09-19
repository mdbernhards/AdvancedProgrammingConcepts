//
// Created by Dawid Zalewski on 17/08/2021.
//

#ifndef LESSON_LOGGER_H
#define LESSON_LOGGER_H

#include <memory>
#include "ilogger.h"
#include "itime_source.h"
#include "itext_writer.h"

namespace lib
{
    class logger: public lib::ilogger 
    {
        public:
            logger(std::unique_ptr<writers::itext_writer> out);
            logger() noexcept;

            void log(const std::string_view& msg) const override;
            void setTimeSource(std::unique_ptr<time_source::itime_source> source);
        private:
            std::unique_ptr<time_source::itime_source> timeSource;
            std::unique_ptr<writers::itext_writer> m_writer;
    };
}

#endif //LESSON_LOGGER_H