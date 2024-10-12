//
// Created by dza02 on 8/28/2021.
//

#ifndef LESSON_MULTI_WRITER_H
#define LESSON_MULTI_WRITER_H

#include "itext_writer.h"
#include <unordered_map>
#include <string_view>
#include <memory>
#include <string>

namespace writers {
    class multi_writer : public io::itext_writer {
    public:
        multi_writer();

        void add_writer(const std::string& name, std::unique_ptr<io::itext_writer> writer);
        void remove_writer(const std::string& name);

        virtual ~multi_writer() override = default;

        virtual itext_writer& operator<<(std::string_view view) override;

        virtual itext_writer& operator<<(const char* string) override;

        virtual itext_writer& operator<<(char c) override;

        virtual itext_writer& operator<<(int n) override;

        virtual itext_writer& operator<<(io::flush_t flush) override;

    private:
        std::unordered_map<std::string, std::unique_ptr<io::itext_writer>> m_writers;
    };
}


#endif //LESSON_MULTI_WRITER_H
