//
// Created by dza02 on 9/9/2021.
//

#ifndef ADVANCED_PROGRAMMING_CONCEPTS_1_RUNTIME_DECORATOR_H
#define ADVANCED_PROGRAMMING_CONCEPTS_1_RUNTIME_DECORATOR_H

#include <chrono>
#include "decorator.h"

namespace lib::decorators {

    class runningtime_decorator: public decorator {
    public:
        using decorator::decorator;
        virtual void log(std::string_view msg) const override;
    private:
       // const inline static std::chrono::time_point<std::chrono::high_resolution_clock> s_start_time {std::chrono::high_resolution_clock::now()};
    };

}

#endif //ADVANCED_PROGRAMMING_CONCEPTS_1_RUNTIME_DECORATOR_H
