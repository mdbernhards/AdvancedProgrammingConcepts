#include "decorator.h"

namespace lib::decorators
{
    decorator::decorator(std::unique_ptr<loggers::ilogger> inner):
        m_inner{ std::move(inner) }
    {

    }

    void decorator::log(std::string_view msg) const
    {
        m_inner->log(msg);
    }
}