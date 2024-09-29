#include "clogger_adapter.h"
#include "logger.h"

namespace lib
{
    clogger_adapter::clogger_adapter(std::chrono::seconds roll_interval)
    {
        time_t interval_in_seconds = roll_interval.count();
        lg_result_e result = lg_create(&m_clogger, interval_in_seconds);
        
        if (result != lgr_ok) 
        {
            throw std::runtime_error("lg_create error in creating logger");
        }
    }

    clogger_adapter::~clogger_adapter()
    {
        if (m_clogger) 
        {
            lg_result_e result = lg_destroy(&m_clogger);
            if (result != lgr_ok) {
                // You can log an error or handle it if needed
            }
        }
    }
    
    void clogger_adapter::log(std::string_view msg) const
    {
        if (!m_clogger) 
        {
            throw std::runtime_error("Logger is not initialized");
        }

        lg_result_e result = lg_log(m_clogger, msg.data());

        if (result != lgr_ok) 
        {
            throw std::runtime_error("lg_log failed to log message");
        }
    }
}