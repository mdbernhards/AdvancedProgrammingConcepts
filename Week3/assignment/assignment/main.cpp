//
// Created by dza02 on 9/5/2021.
//

#include "logger.h"
#include "program.h"
#include "console_writer.h"
#include "stream_writer.h"
#include "file_writer_adapter.h"
#include "multi_writer.h"
#include "decorators/timestamp_decorator.h"
#include "decorators/runningtime_decorator.h"
#include "clib/logger.h"
#include "builders/logger_builder.h"

#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <cstdbool>

void demo_lg_logger(){
    lg_logger_t* logger{nullptr};
    lg_create(&logger, 3);
    lg_set_debug_output(logger, true);

    lg_log(logger, "Hello world");
    std::this_thread::sleep_for(std::chrono::seconds{6});
    lg_log(logger, "Once more...");
    std::this_thread::sleep_for(std::chrono::seconds{6});
    lg_log(logger, "And once more...");

    lg_destroy(&logger);
}

int main(){
    auto log = builders::default_builder()
        .with_console_output()
        .with_file_output("out5.txt")
        .with_timestamp(builders::ilogger_builder::timestamp_type::running_time)
        .get();

    program prog { std::move(log) };
    prog.run();

    std::this_thread::sleep_for(std::chrono::seconds(1)); // to seperate 

    auto log2 = builders::default_builder()
        .with_writer(std::make_unique<writers::console_writer>())
        .with_file_output("out6.txt")
        .with_timestamp(builders::ilogger_builder::timestamp_type::current_time)
        .with_timestamp(builders::ilogger_builder::timestamp_type::running_time)
        .get();
    
    prog.set_logger(std::move(log2));
    prog.run();

    std::this_thread::sleep_for(std::chrono::seconds(1)); // to seperate 

    auto log3 = builders::default_builder()
        .with_writer(std::make_unique<writers::console_writer>())
        .with_file_output("out7.txt")
        .with_timestamp(builders::ilogger_builder::timestamp_type::current_time)
        .with_rolling_log_with_interval(std::chrono::seconds(2))
        .get();
    
    prog.set_logger(std::move(log3));
    prog.run();
}