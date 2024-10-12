//
// Created by dza02 on 8/28/2021.
//

#ifndef LESSON_ITEXT_WRITER_H
#define LESSON_ITEXT_WRITER_H

struct itext_writer {
    virtual void write(const char*) = 0;
    virtual void write(char c) = 0;

    virtual ~itext_writer() = default;
};

#endif //LESSON_ITEXT_WRITER_H
