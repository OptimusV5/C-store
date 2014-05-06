#ifndef LOAD
#define LOAD
#include <cstdio>
#include <cstdlib>
class load {
public:
    load();
    virtual int fRead();
    virtual void fWrite(int);
    //virtual void fSeek(int);
    virtual void fWork();
    //virtual void RLE(char*) = 0;
    ~load();
private:
    int *page_int[4];
    double *page_dec;
    FILE *fIn;
    FILE *fOut[4];
    FILE *fPtr;
    char file_name[4][40];
};
#endif
