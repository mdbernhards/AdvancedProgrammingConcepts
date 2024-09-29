//
// Created by dza02 on 8/28/2021.
//

#include "decorators/runningtime_decorator.h"
#include <sstream>
#include <iomanip>

void lib::decorators::runningtime_decorator::log(std::string_view msg) const 
{
    // s_start_time is the name of the private variable that holds the starting time
    auto running_time = std::chrono::high_resolution_clock::now() - s_start_time;

    // full seconds of the running time
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(running_time);
    running_time -= seconds;

    // remaining nanoseconds of the running time
    auto nano = std::chrono::duration_cast<std::chrono::nanoseconds>(running_time);

    std::ostringstream oss;
    oss << '[' << seconds.count() << '.' << std::setfill('0') << std::setw(9) << nano.count() << "s] " << msg;
    auto str = oss.str();

    decorator::log(str);
}
