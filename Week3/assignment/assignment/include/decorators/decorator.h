// Created by dza02 on 9/9/2021.
//

#ifndef ADVANCED_PROGRAMMING_CONCEPTS_1_DECORATOR_H
#define ADVANCED_PROGRAMMING_CONCEPTS_1_DECORATOR_H

#include <multi_writer.h>
#include <memory>
#include "ilogger.h"

namespace lib::decorators {
    class decorator: public loggers::ilogger {
    public:

        decorator(std::unique_ptr <ilogger> inner) : m_inner( std::move(inner) ) {}

        virtual void log(std::string_view msg) const override {
            m_inner->log(msg);
        }

    private:
        std::unique_ptr<loggers::ilogger> m_inner;
    };
}


#endif //ADVANCED_PROGRAMMING_CONCEPTS_1_DECORATOR_H
