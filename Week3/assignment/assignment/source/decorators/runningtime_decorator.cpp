//
// Created by dza02 on 9/9/2021.
//

#include <sstream>
#include <iomanip>

#include "decorators/runningtime_decorator.h"
#include "global/runningtime_provider.h"


void lib::decorators::runningtime_decorator::log(std::string_view msg) const {
    std::ostringstream oss;

    auto running_time = global::runningtime_provider::get_instance().running_time();

    // full seconds of the runing time
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(running_time);
    running_time -= seconds;

    // remaining nanoseconds of the running time
    auto nano = std::chrono::duration_cast<std::chrono::nanoseconds>(running_time);

    oss << '[' << seconds.count() << '.' << std::setfill('0') << std::setw(9) << nano.count() << "] " << msg;
    auto str = oss.str();
    decorator::log(str);
}