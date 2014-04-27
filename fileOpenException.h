#ifndef FILE_OPEN_EXCEPTION
#define FILE_OPEN_EXCEPTION
#include "fileException.h"
#include <iostream>
using namespace std;
class FileOpenException : public FileException {
public:
    FileOpenException();
    FileOpenException(const char*);
    virtual void print();
private:
    const char *s;
};

#endif
