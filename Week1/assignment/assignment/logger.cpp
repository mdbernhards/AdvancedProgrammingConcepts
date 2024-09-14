//
// Created by Dawid Zalewski on 22/08/2021.
//

#include "logger.h"
#include <ctime>

namespace lib{

    logger::logger(std::ostream& m_out) noexcept : m_out{m_out} {}

    logger::logger() noexcept : logger(std::cout) {}

    void logger::log(const std::string& msg) const{
        m_out << '[';
        output_time();
        m_out << "]: " <<  msg << '\n';
    }

    void logger::output_time() const {
        auto time_point = std::time(nullptr);
        auto local_time = std::localtime(&time_point);
        char buffer[16];
        std::strftime(&buffer[0], sizeof(buffer),"%H:%M:%S", local_time);
        m_out << buffer;
    }
}