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

#include "clib/logger.h"
#include <iostream>
#include <memory>
#include <thread>
#include <chrono>

/*
 * this demonstrates the rolling logger functionality
 * It logs three messages using the C-API in 6 second intervals.
 * Since the rolling interval is set to 3 seconds, three different log files will be generated.
 * (They are located in cmake-build-[debug|release]/assignment/)
 */
void demo_rolling(){
    lg_logger_t* logger{nullptr};
    lg_create(&logger, 3);
    // just to print output on logging
    lg_set_debug_output(logger, true);

    lg_log(logger, "Hello world (logged to the first file)");
    std::this_thread::sleep_for(std::chrono::seconds{6});
    lg_log(logger, "Once more... (logged to the second file)");
    std::this_thread::sleep_for(std::chrono::seconds{6});
    lg_log(logger, "And once more...(logged to the third file)");

    lg_destroy(&logger);
}

int main(){

    auto fwa = std::make_unique<writers::file_writer_adapter>("_out2.txt");
    auto sw = std::make_unique<writers::stream_writer>("_out1.txt");
    auto cw = std::make_unique<writers::console_writer>();

    auto mw = std::make_unique<writers::multi_writer>();

    mw->add_writer("fwa", std::move(fwa));
    mw->add_writer("sw", std::move(sw));
    mw->add_writer("cw", std::move(cw));

    auto log = std::make_unique<lib::logger>( std::move(mw) );

    auto decorated = std::make_unique<lib::decorators::timestamp_decorator>(std::move(log));
    program prog{ std::move(decorated) };
    prog.run();

    // uncomment to see lg_logger in action
    // demo_rolling();

}