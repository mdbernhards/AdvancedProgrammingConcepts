//
// Created by dza02 on 9/6/2021.
//

#include "global/runningtime_provider.h"

/* a dummy object to trigger the singleton creation */
[[maybe_unused]] static auto nothing = global::runningtime_provider::get_instance().start_time();

global::runningtime_provider::time_point global::runningtime_provider::start_time() const noexcept {
    return m_t0;
}

global::runningtime_provider::duration global::runningtime_provider::running_time() const noexcept {
    return std::chrono::high_resolution_clock::now() - m_t0;
}

global::runningtime_provider::runningtime_provider():
    m_t0{std::chrono::high_resolution_clock::now()}
{}

const global::runningtime_provider& global::runningtime_provider::get_instance() {
    static runningtime_provider obj{};
    return obj;
}
