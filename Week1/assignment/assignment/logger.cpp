//
// Created by Dawid Zalewski on 22/08/2021.
//

#include "logger.h"

namespace lib{

    logger::logger(std::ostream& m_out) noexcept : m_out{m_out} {}

    logger::logger() noexcept : logger(std::cout) {}

    void logger::log(const std::string& msg) const{
        m_out << '[';
        output_time();
        m_out << "]: " <<  msg << '\n';
    }
}