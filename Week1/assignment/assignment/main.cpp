//
// Created by Dawid Zalewski on 9/5/2021.
//

#include "logger.h"
#include "program.h"
#include <iostream>
#include <memory>

int main(){
    auto log = std::make_unique<lib::logger>( );
    program prog{ std::move(log) };
    prog.run();
}