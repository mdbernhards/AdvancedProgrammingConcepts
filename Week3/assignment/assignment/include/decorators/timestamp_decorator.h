//
// Created by dza02 on 8/28/2021.
//

#ifndef LESSON_TIMESTAMP_DECORATOR_H
#define LESSON_TIMESTAMP_DECORATOR_H

#include <string>
#include <memory>
#include "decorator.h"

namespace lib::decorators {

class timestamp_decorator: public decorator {
public:
    using decorator::decorator;
    virtual void log(std::string_view msg) const override;
};
}

#endif //LESSON_TIMESTAMP_DECORATOR_H
