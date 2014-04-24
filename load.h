#ifndef LOAD
#define LOAD
#include <cstdio>
#include <cstdlib>
class load {
public:
	load();
	virtual void fRead();
	virtual void fWrite();
	//virtual void fSeek(int);
	virtual void fWork();
	//virtual void RLE(char*) = 0;
	~load();
private:
	int *page_int[4];
	double *page_dec;
	FILE *fIn;
        FILE *fOut[4];
	char file_name[4][20];
};
#endif
