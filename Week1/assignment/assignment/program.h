//
// Created by Dawid Zalewski on 9/5/2021.
//

#ifndef ADVANCED_PROGRAMMING_CONCEPTS_1_PROGRAM_H
#define ADVANCED_PROGRAMMING_CONCEPTS_1_PROGRAM_H

#include "logger.h"
#include <memory>

class program {
public:
    explicit program(std::unique_ptr<loggers::ilogger> some_logger) noexcept;
    ~program() noexcept;

    void set_logger(std::unique_ptr<loggers::ilogger> some_logger) noexcept;
    void run();
private:
    std::unique_ptr<loggers::ilogger> m_logger;
};

#endif //ADVANCED_PROGRAMMING_CONCEPTS_1_PROGRAM_H
