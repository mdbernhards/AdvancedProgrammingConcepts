//
// Created by dza02 on 8/28/2021.
//

#ifndef LESSON_IO_ITEXT_WRITER_H
#define LESSON_IO_ITEXT_WRITER_H
#include <string_view>

namespace io {

    namespace detail {
        struct _flush {
        };
    }

    using flush_t = detail::_flush;
    inline flush_t flush;

    struct itext_writer {
        virtual itext_writer& operator<<(std::string_view) = 0;
        virtual itext_writer& operator<<(const char*) = 0;
        virtual itext_writer& operator<<(char c) = 0;
        virtual itext_writer& operator<<(int n) = 0;

        virtual itext_writer& operator<<(flush_t) = 0;

        virtual ~itext_writer() = default;
    };
}

#endif //LESSON_IO_ITEXT_WRITER_H
