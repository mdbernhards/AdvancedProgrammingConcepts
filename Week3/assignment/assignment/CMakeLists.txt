
add_executable(assignment)
target_include_directories(assignment PRIVATE include)

target_sources(assignment
        PRIVATE
        main.cpp
        )

add_subdirectory(source)

add_subdirectory(clib)
target_link_libraries(assignment PRIVATE clogger)

list(APPEND TARGETS assignment)
set(TARGETS ${TARGETS} PARENT_SCOPE)