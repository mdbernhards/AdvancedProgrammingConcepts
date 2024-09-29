//
// Created by dza02 on 9/5/2021.
//

#include "logger.h"
#include "program.h"
#include "console_writer.h"
#include "stream_writer.h"
#include "file_writer_adapter.h"
#include "multi_writer.h"
#include "clogger_adapter.h"
#include "decorators/timestamp_decorator.h"
#include "decorators/runningtime_decorator.h"
#include "clib/logger.h"

#include <iostream>
#include <memory>
#include <thread>
#include <chrono>

int main()
{
    //I'm not sure why but sometimes lg_create starts returning error code. Only fix I found was restarting vs code

    auto log = std::make_unique<lib::clogger_adapter>(std::chrono::seconds{5});
    auto runningtime_decorator = std::make_unique<lib::decorators::runningtime_decorator>(std::move(log));

    program prog{ std::move(runningtime_decorator) };
    prog.run();

    std::this_thread::sleep_for(std::chrono::seconds(2)); // to have separate log files, so that it doesn't get overwritten

    auto log2 = std::make_unique<lib::clogger_adapter>(std::chrono::seconds{5});
    auto timestamp_decorator = std::make_unique<lib::decorators::timestamp_decorator>(std::move(log2));
    
    prog.set_logger(std::move(timestamp_decorator));

    prog.run();
    
    return 0;
}