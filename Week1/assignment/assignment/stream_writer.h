#ifndef LESSON_StreamWriter_H
#define LESSON_StreamWriter_H

#include <string_view>
#include <fstream>
#include "itext_writer.h"

namespace writers 
{
    class stream_writer: public itext_writer
    {
        public:
            stream_writer(const std::string& filename);
            itext_writer& operator<<(std::string_view text) override;
            itext_writer& operator<<(const char* text) override;
            itext_writer& operator<<(char c) override;
        private:
            std::ofstream m_file;
    };
}

#endif // LESSON_StreamWriter_H