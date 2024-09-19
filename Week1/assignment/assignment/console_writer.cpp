#include "console_writer.h"
#include <iostream>

namespace writers 
{
    itext_writer& console_writer::operator<<(std::string_view text) 
    {
        std::cout << text;
        return *this;
    }

    itext_writer& console_writer::operator<<(const char* text)
    {
        std::cout << text;
        return *this;
    }

    itext_writer& console_writer::operator<<(char c)
    {
        std::cout << c;
        return *this;
    }
}