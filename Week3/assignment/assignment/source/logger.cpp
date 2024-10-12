//
// Created by Dawid Zalewski on 22/08/2021.
//

#include "logger.h"
#include <ctime>

namespace lib{

    void logger::log(std::string_view msg) const{
        *m_out << msg << '\n';
    }

    logger::logger(std::unique_ptr<io::itext_writer> out) : m_out{std::move(out)}{}

    void logger::set_writer(std::unique_ptr<io::itext_writer> out) {
        m_out.reset(out.release());
    }
}