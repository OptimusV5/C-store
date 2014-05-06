#include "fileOpenException.h"
#include <cstdio> 
FileOpenException::FileOpenException() {
    s = NULL;
}
FileOpenException::FileOpenException(const char* _s) {
    s = _s;
}
void FileOpenException::print() {
    printf("File %s not found! \n",s);
}
