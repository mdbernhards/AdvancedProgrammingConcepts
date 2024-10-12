//
// Created by dza02 on 8/28/2021.
//

#ifndef LESSON_FILE_WRITER_H
#define LESSON_FILE_WRITER_H

#include <cstdio>
#include "itext_writer.h"

class file_writer : public itext_writer {
public:

    file_writer(const char* fname);

    virtual void write(char c) override;

    virtual void write(const char* string) override;

    virtual ~file_writer() override;



protected:
    file_writer();
    void write(const char* string, std::FILE* file);
    void write(char c, std::FILE* file);

private:
    std::FILE* m_file;
};


#endif //LESSON_FILE_WRITER_H
