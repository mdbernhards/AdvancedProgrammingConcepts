#include "clogger_as_writer.h"

io::clogger_as_writer::clogger_as_writer(std::chrono::seconds roll_interval)
{
    time_t interval_in_seconds = roll_interval.count();
    lg_result_e result = lg_create(&m_clogger, interval_in_seconds);
    
    if (result != lgr_ok) 
    {
        throw std::runtime_error("lg_create error in creating logger");
    }
}

io::clogger_as_writer::~clogger_as_writer()
{
    if (m_clogger) 
    {
        [[maybe_unused]] lg_result_e result = lg_destroy(&m_clogger);
    }
}

io::itext_writer& io::clogger_as_writer::operator<<(char c)
{
    char temp[2];

    printf(temp, "%c", c);
    lg_log(m_clogger, temp);

    return *this;
}

io::itext_writer& io::clogger_as_writer::operator<<(int n)
{
    char temp[11];

    printf(temp, "%d", n);
    lg_log(m_clogger, temp);

    return *this;
}

io::itext_writer& io::clogger_as_writer::operator<<(io::flush_t)
{
    return *this;
}

io::itext_writer& io::clogger_as_writer::operator<<(std::string_view str)
{
    lg_result_e result = lg_log(m_clogger, str.data());

    if (result != lgr_ok) 
    {
        throw std::runtime_error("lg_log failed to log message");
    }

    return *this;
}

io::itext_writer& io::clogger_as_writer::operator<<(const char* str) 
{
    lg_log(m_clogger, str);

    return *this;
}