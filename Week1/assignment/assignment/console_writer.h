#ifndef LESSON_ConsoleWriter_H
#define LESSON_ConsoleWriter_H

#include <string_view>
#include "itext_writer.h"

namespace writers 
{
    class console_writer: public itext_writer
    {
        public:
            itext_writer& operator<<(std::string_view text) override;
            itext_writer& operator<<(const char* text) override;
            itext_writer& operator<<(char c) override;
    };
}

#endif // LESSON_ConsoleWriter_H