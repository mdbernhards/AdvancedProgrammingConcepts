//
// Created by Dawid Zalewski on 17/08/2021.
//

#ifndef LESSON_LOGGER_H
#define LESSON_LOGGER_H

#include <string>
#include <iostream>
#include "ilogger.h"

namespace lib{
class logger: public loggers::ilogger {
    public:
        explicit logger(std::ostream& out) noexcept;
        logger() noexcept;
        void log(const std::string& msg) const override;
    private:
        std::ostream& m_out;
        void output_time() const;
    };
}

#endif //LESSON_LOGGER_H
