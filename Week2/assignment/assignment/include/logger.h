//
// Created by Dawid Zalewski on 17/08/2021.
//

#ifndef LESSON_LOGGER_H
#define LESSON_LOGGER_H

#include <string>
#include <iostream>
#include <memory>
#include "ilogger.h"
#include "itext_writer.h"

namespace lib{
class logger: public loggers::ilogger {
    public:
        explicit logger(std::unique_ptr<io::itext_writer> out);
        void set_writer(std::unique_ptr<io::itext_writer> out) noexcept;

        void log(std::string_view msg) const override;
    private:
        std::unique_ptr<io::itext_writer> m_out;
    };
}

#endif //LESSON_LOGGER_H
