cmake_minimum_required(VERSION 3.18)

project(apc_07_move_semantics)

add_executable(vector_fun main.cpp)

target_compile_features(vector_fun PRIVATE cxx_std_20)

set_target_properties(vector_fun PROPERTIES CXX_EXTENSIONS OFF)

target_compile_options(vector_fun PRIVATE $<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra -Wpedantic -fno-omit-frame-pointer -g3 -Og>
                                          $<$<CXX_COMPILER_ID:Clang>:-Wall -Wextra -Wpedantic -fno-omit-frame-pointer -g3 -Og>
                                          $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX /analyze>)

# sanitizers for gcc/clang

target_compile_options(vector_fun PRIVATE $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-fsanitize=address,undefined>
                                          $<$<CXX_COMPILER_ID:GNU>:-fno-sanitize-recover=all -fstack-protector-strong>
                                          $<$<CXX_COMPILER_ID:Clang>:-fno-sanitize-recover=all -fstack-protector-strong>)

target_link_options(vector_fun PRIVATE $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-fsanitize=address,undefined>)

