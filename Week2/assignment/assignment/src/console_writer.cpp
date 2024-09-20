//
// Created by dza02 on 8/28/2021.
//

#include <iostream>
#include "console_writer.h"

io::itext_writer& writers::console_writer::operator<<(std::string_view view) {
    m_out << view;
    return *this;
}

io::itext_writer& writers::console_writer::operator<<(const char* string) {
    m_out << string;
    return *this;
}

io::itext_writer& writers::console_writer::operator<<(char c) {
    m_out << c;
    return *this;
}

io::itext_writer& writers::console_writer::operator<<(int n) {
    m_out << n;
    return *this;
}

io::itext_writer& writers::console_writer::operator<<(io::flush_t) {
    m_out << std::flush;
    return *this;
}
