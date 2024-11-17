# download and populate Google Test from githu
include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        v1.14.0
)

# for Windows: prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()

set(target tests_algos)
add_executable(${target} algo_tests.cpp test_runner.cpp)


if (HAS_ASAN AND USE_ASAN)
    message(STATUS "Enabling ASAN & UBSAN for ${target}")
    target_compile_options(${target} PRIVATE -fsanitize=address,undefined -fsanitize-recover=address,undefined )
    target_link_options(${target} PRIVATE -fsanitize=address,undefined)
endif ()

include(GoogleTest)

target_compile_features(${target} PRIVATE cxx_std_20)
set_target_properties(${target} PROPERTIES CXX_EXTENSIONS OFF)

target_link_libraries(${target} gtest gmock)
target_link_libraries(${target} lib_algos)

gtest_discover_tests(${target})