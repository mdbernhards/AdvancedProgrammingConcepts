//
// Created by Dawid Zalewski on 9/5/2021.
//

#include "logger.h"
#include "program.h"
#include "itext_writer.h"
#include "console_writer.h"
#include "stream_writer.h"
#include "system_time_source.h"
#include <iostream>
#include <memory>

int main()
{
    auto logger = std::make_unique<lib::logger>( std::make_unique<writers::console_writer>() );
    logger->setTimeSource(std::make_unique<time_source::system_time_source>());
    
    program prog{std::move(logger)};
    prog.run();

    auto logger2 = std::make_unique<lib::logger>(std::make_unique<writers::stream_writer>("log.txt"));
    logger2->setTimeSource(std::make_unique<time_source::system_time_source>());
    program prog2{std::move(logger2)};
    prog2.run();
}