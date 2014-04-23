#include "load.h"
#include <cstring>

load::load() {
    for (int i = 0; i < 4; i++)
		page_int[i] = NULL;
	page_dec = NULL;
	fPtr = NULL;
	strcpy(file_name[0] , "orderkey.fjl");
	strcpy(file_name[1] , "custkey.fjl");
	strcpy(file_name[2] , "shippriority.fjl");
	strcpy(file_name[3] , "totalprice.fjl");
	fWork();
}

void load::fRead() {

	for (int j = 0; j < 2048; j++) {
		for (int i = 0; i < 4; i++) {
			if (i != 2)
				fscanf(fPtr, "%d", &page_int[i][j]);
		    else
				fscanf(fPtr, "%lf", &page_dec[j]);
            fSeek(i);
			if (feof(fPtr))
				return;
		}
	}
}

void load::fWrite() {
	for (int i = 0; i < 4; i++) {
	    FILE *f = fopen(file_name[i],"ab");
		if (i != 2)
			fwrite(page_int[i], sizeof(int), 2048, f);
		else
			fwrite(page_dec, sizeof(double), 2048, f);
	}
}

void load::fSeek(int i) {
	if (i == 0)
		fseek(fPtr, 1L, SEEK_CUR);
    if (i == 1)
		fseek(fPtr, 3L, SEEK_CUR);
	if (i == 2)
		fseek(fPtr, 44L, SEEK_CUR);
	if (i == 3) {
	    char sTemp[80];
	    fgets(sTemp, 80, fPtr);
	}
}
void load::fWork() {
	fPtr = fopen("orders.tbl","rt");
    while(!feof(fPtr)) {
		for (int i = 0; i < 4; i++) {
			if (i != 2)
			page_int[i] = new int[2048];
		}
		page_dec = new double[2048];
	    fRead();
		fWrite();
		for (int i = 0; i < 4; i++) {
		    if (i != 2) {
				delete page_int[i];
			    page_int[i] = NULL;
			} else {
			    delete page_dec;
				page_dec = NULL;
			}
		}
	}
	fclose(fPtr);
}

load::~load() {
}
