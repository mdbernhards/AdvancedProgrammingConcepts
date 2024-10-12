//
// Created by dza02 on 8/28/2021.
//

#include <iostream>
#include "console_writer.h"

io::itext_writer& writers::console_writer::operator<<(std::string_view view) {
    std::cout << view;
    return *this;
}

io::itext_writer& writers::console_writer::operator<<(const char* string) {
    std::cout << string;
    return *this;
}

io::itext_writer& writers::console_writer::operator<<(char c) {
    std::cout << c;
    return *this;
}

io::itext_writer& writers::console_writer::operator<<(int n) {
    std::cout << n;
    return *this;
}

io::itext_writer& writers::console_writer::operator<<(io::flush_t) {
    std::cout << std::flush;
    return *this;
}
