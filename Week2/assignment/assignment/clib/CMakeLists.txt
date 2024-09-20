add_library(clogger STATIC)

target_sources(clogger PRIVATE file_writer.cpp logger.c)

set_target_properties(clogger PROPERTIES
        LANGUAGE CXX
        LINKER_LANGUAGE CXX
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
        )

target_compile_features(clogger PRIVATE cxx_std_17)
target_compile_options(clogger PRIVATE -Wall -Wextra -pedantic -fno-omit-frame-pointer)

target_include_directories(clogger
            INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        )
