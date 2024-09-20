//
// Created by dza02 on 8/28/2021.
//

#ifndef LESSON_TIMESTAMP_DECORATOR_H
#define LESSON_TIMESTAMP_DECORATOR_H

#include <string>
#include <memory>
#include "ilogger.h"

namespace lib::decorators {

class timestamp_decorator: public loggers::ilogger {
public:
    explicit timestamp_decorator(std::unique_ptr<loggers::ilogger> inner) noexcept;
    virtual void log(std::string_view msg) const override;
private:
    std::unique_ptr<loggers::ilogger> m_inner;
};
}

#endif //LESSON_TIMESTAMP_DECORATOR_H
