#include "load.h"
#include <cstring>

load::load() {
	
	strcpy(file_name[0] , "orderkey.fjl");
	strcpy(file_name[1] , "custkey.fjl");
	strcpy(file_name[2] , "shippriority.fjl");
	strcpy(file_name[3] , "totalprice.fjl");
    for (int i = 0; i < 4; i++) {
		page_int[i] = NULL;
	    fOut[i] = NULL;
	}
	page_dec = NULL;
	fIn = NULL;
	fPtr = NULL;	
	fWork();
}
void load::fRead() {
    char sTemp[200];
	for (int i = 0; i < 2048; i++) {
	    if (!fgets(sTemp,200,fIn))
			return;
		int num = 0;
		char *temp;
		temp = strtok(sTemp,"|");
        page_int[0][i] = atoi(temp);
		if (i == 0)
			fwrite(page_int[0],sizeof(int),1,fPtr);
		num++;
		while (temp != NULL) {
		    temp = strtok(NULL,"|");
            if (num == 1)
				page_int[1][i] = atoi(temp);
			if (num == 3)
				page_dec[i] = atof(temp);
			if (num == 7) {
				page_int[3][i] = atoi(temp);
			    break;
			}
			num++;
		}
	}
}

void load::fWrite() {
	for (int i = 0; i < 4; i++) {
	   // FILE *f = fopen(file_name[i],"ab");
		if (i != 2)
			fwrite(page_int[i], sizeof(int), 2048, fOut[i]);
		else
			fwrite(page_dec, sizeof(double), 2048, fOut[i]);
	}
}

/*void load::fSeek(int i) {
	if (i == 0)
		fseek(fIn, 1L, SEEK_CUR);
    if (i == 1)
		fseek(fIn, 3L, SEEK_CUR);
	if (i == 2)
		fseek(fIn, 44L, SEEK_CUR);
	if (i == 3) {
	    char sTemp[80];
	    fgets(sTemp, 80, fIn);
	}
}*/
void load::fWork() {
	fPtr = fopen("index.fjl","wb");
	fIn = fopen("orders.tbl","rt");
	for (int i = 0; i < 4; i++)
		fOut[i] = fopen(file_name[i],"wb");
	int page_num = 0;
	fwrite(&page_num,sizeof(int),1,fPtr);
	while(!feof(fIn)) {
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
		page_num++;
	}
	fseek(fPtr,0L,SEEK_SET);
	fwrite(&page_num,sizeof(int),1,fPtr);
	fclose(fPtr);
	fclose(fIn);
	for (int i = 0; i < 4; i++)
		fclose(fOut[i]);
}

load::~load() {
}
