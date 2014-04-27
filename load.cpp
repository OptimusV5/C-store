#include "load.h"
#include <cstring>
#include "fileOpenException.h"
load::load() {
    //Name the four colomn file
    strcpy(file_name[0] , "orderkey.fjl");
    strcpy(file_name[1] , "custkey.fjl");
    strcpy(file_name[2] , "shippriority.fjl");
    strcpy(file_name[3] , "totalprice.fjl");
    //Initialize 
    for (int i = 0; i < 4; i++) {
        page_int[i] = NULL;
        fOut[i] = NULL;
    }
    page_dec = NULL;
    fIn = NULL;
    fPtr = NULL;    
    fWork();
}

//Read from orders.tbl
void load::fRead() {
    char sTemp[200];
    for (int i = 0; i < 2048; i++) {
        if (!fgets(sTemp,200,fIn))    //Get every line of orders.tbl
            return;
        int num = 0;                  //Count the colomn
        char *temp;
        temp = strtok(sTemp,"|");     //slpit the line
        page_int[0][i] = atoi(temp);                //Get orderkey
        if (i == 0)
            fwrite(page_int[0],sizeof(int),1,fPtr); //Write first orderkey of one page in a file
        num++;
        while (temp != NULL) {
            temp = strtok(NULL,"|");
            if (num == 1)
                page_int[1][i] = atoi(temp);    //Get custkey 
            if (num == 3)
                page_dec[i] = atof(temp);       //Get totalprice
            if (num == 7) {
                page_int[3][i] = atoi(temp);    //Get shippiority
                break;
            }
            num++;
        }
    }  
}

//Write to the file
void load::fWrite() {
    for (int i = 0; i < 4; i++) {
        if (i != 2)
            fwrite(page_int[i], sizeof(int), 2048, fOut[i]); //Write colomn orderkey, custkey, shippriority
        else
            fwrite(page_dec, sizeof(double), 2048, fOut[i]); //Write colomn totalprice
    }
}

//Work!!
void load::fWork() {
    if ((fIn = fopen("orders.tbl","rt")) == NULL) {
        throw FileOpenException("orders.tbl");
    }
    fPtr = fopen("index.fjl","wb");         //A file to store the information of the colomn table
    for (int i = 0; i < 4; i++)
        fOut[i] = fopen(file_name[i],"wb"); //Four colomn file
    int page_num = 0;
    fwrite(&page_num,sizeof(int),1,fPtr);   //Write the total number of pages
    while(!feof(fIn)) {
        //Allocate memory for arrays
        for (int i = 0; i < 4; i++) {
            if (i != 2)
                page_int[i] = new int[2048];
        }
        page_dec = new double[2048];
        fRead();
        fWrite();
        //Delete
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
    fseek(fPtr,0L,SEEK_SET);                  //Move the file pointer to the begining of the file
    fwrite(&page_num,sizeof(int),1,fPtr);     //Writr the amount of page to the file
    //Close all files
    fclose(fPtr);
    fclose(fIn);
    for (int i = 0; i < 4; i++)
        fclose(fOut[i]);
}

//distructer
load::~load() {
}
