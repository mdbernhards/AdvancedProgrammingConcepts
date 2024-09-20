list(APPEND TARGETS assignment)
set(TARGETS ${TARGETS} PARENT_SCOPE)

add_executable(assignment main.cpp)
target_include_directories(assignment PRIVATE include)

add_subdirectory(src)

target_sources(assignment
        PRIVATE
        program.cpp
        )

add_subdirectory(clib)
target_link_libraries(assignment PUBLIC clogger)

list(APPEND TARGETS assignment)
set(TARGETS ${TARGETS} PARENT_SCOPE)