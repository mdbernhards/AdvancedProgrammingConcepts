cmake_minimum_required(VERSION 3.21)
project(advanced_programming_concepts_1)

# add each sub-directory found in the previous step
set(TARGETS "")
add_subdirectory(assignment)


option(USE_ASAN "Use address sanitizer if available" ON)

execute_process(COMMAND "${CMAKE_CXX_COMPILER}" -print-file-name=libasan.so
        OUTPUT_VARIABLE LIBASAN_PATH
        RESULT_VARIABLE ASAN_RESULT
        OUTPUT_STRIP_TRAILING_WHITESPACE)

set(HAS_ASAN FALSE)

if ( USE_ASAN AND (${ASAN_RESULT} EQUAL 0) AND (NOT ${LIBASAN_PATH} STREQUAL ""))
    message("libasan found @${LIBASAN_PATH}")
    message("To disable the address sanitizer set USE_ASAN to OFF.\n")
    set(HAS_ASAN TRUE)
endif ()

# detect clang and gcc
if("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang" OR "${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
    message("CXX compiler is GNU-like")
    set(CXX_GNU_LIKE ON)
else()
    set(CXX_GNU_LIKE OFF)
endif()


foreach(target IN LISTS TARGETS)
    message("Configuring target: ${target}")

    set_target_properties(${target} PROPERTIES
            LANGUAGE CXX
            LINKER_LANGUAGE CXX
            CXX_STANDARD 20
            CXX_STANDARD_REQUIRED ON
            CXX_EXTENSIONS OFF
            )

    target_compile_options(${target} PRIVATE
            # maximum warnings for msvc
            $<$<CXX_COMPILER_ID:MSVC>: /W4>
            # debug optimisation for msvc in debug
            $<$<CXX_COMPILER_ID:MSVC>:$<$<CONFIG:Debug>:/RTC1 /Od /Zi>>
            # O2 optimisation for msvc in release
            $<$<CXX_COMPILER_ID:MSVC>:$<$<CONFIG:Release>:/O2>>
            )

    target_compile_options(${target} PRIVATE
            # set warnings for clang & gcc
            $<$<BOOL:${CXX_GNU_LIKE}>:-Wall -Wextra -Wpedantic -Werror -fno-omit-frame-pointer>
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