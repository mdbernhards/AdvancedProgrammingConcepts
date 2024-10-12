#ifndef LESSON_CLOGGER_AS_WRITER_H
#define LESSON_CLOGGER_AS_WRITER_H

#include <chrono>
#include <stdexcept>
#include <string_view>
#include "ilogger.h"
#include "../clib/logger.h"
#include "itext_writer.h"

namespace io
{
    class clogger_as_writer : public itext_writer 
    {
        public:
            clogger_as_writer(std::chrono::seconds roll_interval);
            ~clogger_as_writer();

            itext_writer& operator<<(char c) override;

            itext_writer& operator<<(int n) override;

            itext_writer& operator<<(io::flush_t) override;

            itext_writer& operator<<(std::string_view str) override;
            
            itext_writer& operator<<(const char*) override;
        private:
            lg_logger_t* m_clogger = NULL; 
    };

}

#endif //LESSON_CLOGGER_AS_WRITER_H