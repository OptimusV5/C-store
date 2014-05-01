#include "query.h"

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

query::query() {}

query::query(int orderid) {
	orderkey = orderid;
	numOfPage = 0;
	offsetOfKey = 0;
	
	for (int i = 0; i < 4; i++)
		result[i] = 0;
	
	result2 = 0;

	for (int i = 0; i < 4; i++)
		fIn[i] = NULL;

	page_int = NULL;
	fIndex = NULL;
	fDec = NULL;

	strcpy(file_name[0], "orderkey.fjl");
	strcpy(file_name[1], "custkey.fjl");
	strcpy(file_name[2], "shippriority.fjl");
	strcpy(file_name[3], "totalprice.fjl");

	Query();
}

int query::pageBinSerach() {
	int low = 0, high = numOfPage - 1; 

	while (low != high - 1) {
		int mid = (low + high) / 2; 

		if (orderkey < page_int[mid])
			high = mid;
		else if (orderkey >= page_int[mid])
			low = mid;
	}

	if (orderkey >= page_int[high])
		return high;
	else
		return low;
}

int query::keyBinSerach() {
	int low = 0, high = 2047; 

	while (low <= high) {
		int mid = (low + high) / 2; 
		if (orderkey == page_int[mid]) { 
			return mid;
		}
		else if (orderkey < page_int[mid]) { 
			high = mid - 1;
		}
		else { 
			low = mid + 1;
		}
	}
	return -1; 
}


void query::LocatePage() {
	int offset = 0;
	page_int = new int[numOfPage];
    fread(page_int, sizeof(int), numOfPage, fIndex);
	int temp = pageBinSerach();
	offsetOfKey = 2048 * sizeof(int)* temp;
	delete []page_int;                                        //page_int is an array
}

void query::LocateOrderkey() {
	page_int = new int[2048];
	int temp = -1;
	if (offsetOfKey == 2048 * sizeof(int) * (numOfPage - 1)) { //The last page should use Traversal method
		for (int i = 0; i < 2048; i++)
			page_int[i] = -1;
		fread(page_int, sizeof(int), 2048, fIn[0]);
		for (int i = 0; i < 2048; i++) {
			if (page_int[i] == orderkey)
				temp = i;
		}
	}
	else {
		fread(page_int, sizeof(int), 2048, fIn[0]);
		temp = keyBinSerach();
	}
	if (temp == -1)
		offsetOfKey = -1;
	else
		offsetOfKey += temp * sizeof(int);                    //sizeof(int) must be mutiplied

	delete []page_int;                                        //page_int is an array
}

void query::Query() {
	fIndex = fopen("index.fjl", "rb");              //open with "rb" !
	fread(&numOfPage, sizeof(int), 1, fIndex);

	LocatePage();									//Locate which page the orderkey in

	fIn[0] = fopen(file_name[0], "rb");
	fseek(fIn[0], offsetOfKey, SEEK_SET);			//move ptr to THE PAGE

	LocateOrderkey();								//Locate where the orderkey is

	if (offsetOfKey == -1) {
		printf("Can not find %d in orders.tbl\n", orderkey);
	}
	else {
		fseek(fIn[0], offsetOfKey, SEEK_SET);				//move ptrs to THE PLACE

		for (int i = 1; i < 4; i++) {
			if (i != 2) {
				fIn[i] = fopen(file_name[i], "rb");
				fseek(fIn[i], offsetOfKey, SEEK_CUR);
			}
		}

		fDec = fopen("shippriority.fjl", "rb");
		fseek(fDec, 2 * offsetOfKey, SEEK_CUR);

		for (int i = 0; i < 4; i++) {
			if (i != 2) {
				fread(&result[i], sizeof(int), 1, fIn[i]);
			}
		}

		fread(&result2, sizeof(double), 1, fDec);

		printf("%10d\t%10d\t%15.2lf\t%10d\n", result[0], result[1], result2, result[3]); //according to the PDF "project cstore"
	}

	fclose(fIndex);
	fclose(fDec);

	for (int i = 0; i < 4; i++)
		fclose(fIn[i]);
}

query::~query() {

}
