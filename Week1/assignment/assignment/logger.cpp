//
// Created by Dawid Zalewski on 22/08/2021.
//

#include <iostream>
#include "logger.h"

namespace lib
{
    logger::logger(std::unique_ptr<writers::itext_writer> out) 
    {
        m_writer = std::move(out);
    }

    logger::logger() noexcept { }

    void logger::log(const std::string_view& msg) const 
    {
        *m_writer << '[';
        *m_writer << timeSource->output_time();
        *m_writer << "]: " << msg << '\n';
    }

    void logger::setTimeSource(std::unique_ptr<time_source::itime_source> source)
    {
        timeSource = std::move(source);
    }
}