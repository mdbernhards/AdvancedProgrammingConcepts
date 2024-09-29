//
// Created by dza02 on 8/28/2021.
//

#ifndef LESSON_RUNNINGTIME_DECORATOR_H
#define LESSON_RUNNINGTIME_DECORATOR_H

#include <chrono>
#include "decorator.h"

namespace lib::decorators 
{
    class runningtime_decorator: public lib::decorators::decorator 
    {
        public:
            using decorator::decorator;
            virtual void log(std::string_view msg) const override;
        private:
            static inline std::chrono::time_point<std::chrono::high_resolution_clock> s_start_time = 
                std::chrono::high_resolution_clock::now();
    };
}

#endif // LESSON_RUNNINGTIME_DECORATOR_H
