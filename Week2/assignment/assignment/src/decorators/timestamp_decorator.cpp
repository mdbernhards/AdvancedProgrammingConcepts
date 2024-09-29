//
// Created by dza02 on 8/28/2021.
//

#include "decorators/timestamp_decorator.h"
#include <ctime>
#include <sstream>
#include <iomanip>

static const char* TIME_FMT = "%H:%M:%S";

void lib::decorators::timestamp_decorator::log(std::string_view msg) const 
{

    std::ostringstream oss;

    auto time_point = std::time(nullptr);
    auto local_time = std::localtime(&time_point);

    oss << '[' << std::put_time(local_time, TIME_FMT) << "] " << msg;
    auto str = oss.str();

    decorator::log(str);
}
