#ifndef LESSON_ITextWriter_H
#define LESSON_ITextWriter_H

#include <string_view>

namespace writers 
{
    struct itext_writer {
        virtual itext_writer& operator<<(std::string_view text) = 0;
        virtual itext_writer& operator<<(const char* text) = 0;
        virtual itext_writer& operator<<(char c) = 0;
        virtual ~itext_writer() = default;
    };
}

#endif //LESSON_ITextWriter_H