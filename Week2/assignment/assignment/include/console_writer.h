//
// Created by dza02 on 8/28/2021.
//

#ifndef LESSON_CONSOLE_WRITER_H
#define LESSON_CONSOLE_WRITER_H

#include "stream_writer.h"

namespace writers {
class console_writer : public io::itext_writer {
public:

    console_writer() = default;

    virtual itext_writer& operator<<(std::string_view view) override;

    virtual itext_writer& operator<<(const char* string) override;

    virtual itext_writer& operator<<(char c) override;

    virtual itext_writer& operator<<(int n) override;

    virtual itext_writer& operator<<(io::flush_t) override;
private:
    std::ostream& m_out{std::cout};
};
}


#endif //LESSON_CONSOLE_WRITER_H
