cmake_minimum_required(VERSION 3.20)
project(apc_assignment_3)

list(APPEND TARGET_DIRS assignment)

# add each sub-directory found in the previous step
set(TARGETS "")
foreach(target ${TARGET_DIRS})
    add_subdirectory(${target})
endforeach()

option(USE_ASAN "Use address sanitizer if available" ON)

set(HAS_ASAN FALSE)

if (USE_ASAN)
    message("USE_ASAN set to ON. If you get errors about libasan, set USE_ASAN to OFF in the main CMakeLists.txt")
    execute_process(COMMAND "${CMAKE_CXX_COMPILER}" -print-file-name=libasan.so
            OUTPUT_VARIABLE LIBASAN_PATH
            RESULT_VARIABLE ASAN_RESULT
            OUTPUT_STRIP_TRAILING_WHITESPACE)


    if ( USE_ASAN AND (${ASAN_RESULT} EQUAL 0) AND (NOT ${LIBASAN_PATH} STREQUAL ""))
        message("libasan found @${LIBASAN_PATH}")
        message("To disable the address sanitizer set USE_ASAN to OFF.\n")
        set(HAS_ASAN TRUE)
    endif ()

endif (USE_ASAN)

# detect clang and gcc
if("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang" OR "${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
    message("CXX compiler is GNU-like")
    set(CXX_GNU_LIKE ON)
else()
    set(CXX_GNU_LIE OFF)
endif()


foreach(target IN LISTS TARGETS)
    message("Configuring target: ${target}")

    target_compile_features(${target} PRIVATE cxx_std_20)
    
    set_target_properties(${target} PROPERTIES
            LANGUAGE CXX
            LINKER_LANGUAGE CXX
            CXX_STANDARD_REQUIRED ON
            CXX_EXTENSIONS OFF
            )

    target_compile_options(${target} PRIVATE
            # maximum warnings for msvc
            $<$<CXX_COMPILER_ID:MSVC>: /W4  /Zc:preprocessor /permissive->
            # debug optimisation for msvc in debug
            $<$<CXX_COMPILER_ID:MSVC>:$<$<CONFIG:Debug>:/RTC1 /Od /Zi>>
            # O2 optimisation for msvc in release
            $<$<CXX_COMPILER_ID:MSVC>:$<$<CONFIG:Release>:/O2>>
            )

    target_compile_options(${target} PRIVATE
            # set warnings for clang & gcc
            $<$<BOOL:${CXX_GNU_LIKE}>:-Wall -Wextra -Wpedantic -Werror -fno-omit-frame-pointer -Wno-gnu-zero-variadic-macro-arguments>
            # debug optimisation for clang & gcc in debug
            $<$<BOOL:${CXX_GNU_LIKE}>:$<$<CONFIG:Debug>:-Og -g>>
            # O3 optimisation for clang & gcc in release
            $<$<BOOL:${CXX_GNU_LIKE}>:$<$<CONFIG:Release>:-O3>>
            )

    # Configuring address sanitizer - only if available and enabled by a user
    if (HAS_ASAN AND USE_ASAN)
        target_compile_options(${target} PRIVATE -fsanitize=address)
        target_link_options(${target} PRIVATE -fsanitize=address)
    endif ()
endforeach()