#ifndef LESSON_Decorator_H
#define LESSON_Decorator_H

#include <string>
#include <memory>
#include "ilogger.h"

namespace lib::decorators
{
    class decorator: public loggers::ilogger 
    {
        public:
            decorator(std::unique_ptr<loggers::ilogger> inner);

            void log(std::string_view msg) const override;
        private:
            std::unique_ptr<loggers::ilogger> m_inner;
    };

}


#endif //LESSON_Decorator_H