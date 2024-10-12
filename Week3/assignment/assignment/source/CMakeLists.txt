target_sources(assignment
        PRIVATE

        program.cpp
        logger.cpp
        stream_writer.cpp
        console_writer.cpp
        multi_writer.cpp
        file_writer_adapter.cpp
        clogger_as_writer.cpp

        decorators/timestamp_decorator.cpp
        decorators/runningtime_decorator.cpp

        builder/logger_builder.cpp

        global/runningtime_provider.cpp

        )