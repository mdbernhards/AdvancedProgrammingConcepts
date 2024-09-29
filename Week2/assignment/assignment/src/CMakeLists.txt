target_sources(assignment
        PRIVATE

        console_writer.cpp
        file_writer_adapter.cpp
        logger.cpp
        multi_writer.cpp
        stream_writer.cpp
        clogger_adapter.cpp
        decorator.cpp
        
        decorators/timestamp_decorator.cpp
        decorators/runningtime_decorator.cpp

        )