
add_executable(assignment program.cpp logger.cpp main.cpp console_writer.cpp console_writer.h ilogger.h itext_writer.h itime_source.h logger.h program.h stream_writer.cpp stream_writer.h system_time_source.cpp system_time_source.h)

list(APPEND TARGETS assignment)
set(TARGETS ${TARGETS} PARENT_SCOPE)

