#include "stream_writer.h"

namespace writers 
{
    stream_writer::stream_writer(const std::string& filename) : m_file(filename) 
    {
        if (!m_file.is_open()) 
        {
            throw std::runtime_error("Failed to open file: " + filename);
        }
    }

    itext_writer& stream_writer::operator<<(std::string_view text)
    {
        m_file << text;
        return *this;
    }

    itext_writer& stream_writer::operator<<(const char* text)
    {
        m_file << text;
        return *this;
    }

    itext_writer& stream_writer::operator<<(char c)
    {
        m_file << c;
        return *this;
    }
}