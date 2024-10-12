add_library(clogger STATIC)

target_sources(clogger PRIVATE file_writer.cpp logger.c)

set_target_properties(clogger PROPERTIES
        LANGUAGE CXX
        LINKER_LANGUAGE CXX
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
        )

target_compile_features(clogger PRIVATE cxx_std_17)
target_compile_options(clogger PRIVATE
        # maximum warnings for msvc
        $<$<CXX_COMPILER_ID:MSVC>: /W4  /Zc:preprocessor /permissive->
        # debug optimisation for msvc in debug
        $<$<CXX_COMPILER_ID:MSVC>:$<$<CONFIG:Debug>:/RTC1 /Od /Zi>>
        # O2 optimisation for msvc in release
        $<$<CXX_COMPILER_ID:MSVC>:$<$<CONFIG:Release>:/O2>>
        )

target_compile_options(clogger PRIVATE
        # set warnings for clang & gcc
        $<$<BOOL:${CXX_GNU_LIKE}>:-Wall -Wextra -Wpedantic -Werror -fno-omit-frame-pointer -Wno-gnu-zero-variadic-macro-arguments>
        # debug optimisation for clang & gcc in debug
        $<$<BOOL:${CXX_GNU_LIKE}>:$<$<CONFIG:Debug>:-Og -g>>
        # O3 optimisation for clang & gcc in release
        $<$<BOOL:${CXX_GNU_LIKE}>:$<$<CONFIG:Release>:-O3>>
        )

target_include_directories(clogger
            INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        )
