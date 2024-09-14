
add_executable(assignment program.cpp logger.cpp main.cpp)

list(APPEND TARGETS assignment)
set(TARGETS ${TARGETS} PARENT_SCOPE)

