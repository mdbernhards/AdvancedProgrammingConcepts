//
// Created by dza02 on 8/28/2021.
//

#ifndef LESSON_STREAM_WRITER_H
#define LESSON_STREAM_WRITER_H


#include <string_view>
#include <memory>
#include "itext_writer.h"

namespace writers {
    class stream_writer : public io::itext_writer {
    public:

        stream_writer(const char* fname);

        stream_writer(std::unique_ptr<std::ostream> out);

        virtual itext_writer& operator<<(std::string_view view) override;

        virtual itext_writer& operator<<(const char* string) override;

        virtual itext_writer& operator<<(char c) override;

        virtual itext_writer& operator<<(int n) override;

        virtual itext_writer& operator<<(io::flush_t) override;

    private:
        std::unique_ptr<std::ostream> m_out;
    };

}

#endif //LESSON_STREAM_WRITER_H
