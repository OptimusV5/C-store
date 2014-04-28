#include "query.h"

#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

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

int query::falseBinSerach() {
	int low = 0, high = numOfPage - 1; // 查找区间初值

	while (low != high - 1)
	{
		int mid = (low + high) / 2; // 查找区间中间位置

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

int query::trueBinSerach() {
	int low = 0, high = numOfPage - 1; // 查找区间初值

	while (low <= high)
	{
		int mid = (low + high) / 2; // 查找区间中间位置
		if (orderkey == page_int[mid])
		{ // 查找成功
			return mid;
		}
		else if (orderkey < page_int[mid])
		{ // 继续在左半区间进行查找
			high = mid - 1;
		}
		else
		{ // 继续在右半区间进行查找
			low = mid + 1;
		}
	}

	return -1; // 查找失败
}


void query::LocatePage() {
	int offset = 0;
	char *buffer = (char*)malloc(sizeof(int));

	page_int = new int[numOfPage];

	for (int i = 0; i < numOfPage; i++) {
		offset += sizeof(int);

		fseek(fIndex, offset, SEEK_SET);
		fread(buffer, sizeof(int), 1, fIndex);

		page_int[i] = atoi(buffer);
	}

	int temp = falseBinSerach();
	offsetOfKey = 2048 * sizeof(int)* temp;

	free(buffer);
	delete page_int;
}

void query::LocateOrderkey() {
	if (offsetOfKey == 2048 * sizeof(int)* (numOfPage - 1)) {
		page_int = new int[(sizeof(fIn[0]) / sizeof(int)) % 2048];
		fread(page_int, sizeof(int), (sizeof(fIn[0]) / sizeof(int)) % 2048, fIn[0]);
	}
	else {
		page_int = new int[2048];
		fread(page_int, sizeof(int), 2048, fIn[0]);
	}

	int temp = trueBinSerach();
	
	if (temp == -1)
		offsetOfKey = -1;
	else
		offsetOfKey += temp;

	delete page_int;
}

void query::Query() {
	fIndex = fopen("index.fjl", "rt");

	char *buffer = (char*)malloc(sizeof(int));

	fread(buffer, sizeof(int), 1, fIndex);

	numOfPage = atoi(buffer);

	LocatePage();									//Locate which page the orderkey in

	fIn[0] = fopen(file_name[0], "rt");
	fseek(fIn[0], offsetOfKey, SEEK_SET);			//move ptr to THE PAGE

	LocateOrderkey();								//Locate where the orderkey is

	if (offsetOfKey == -1) {
		cout << "The result of this query is:\n"
			<< "I can't find " << orderkey << "in order.tbl." << endl;
	}
	else {
		fseek(fIn[0], offsetOfKey, SEEK_SET);				//move ptrs to THE PLACE

		for (int i = 1; i < 4; i++) {
			if (i != 2) {
				fIn[i] = fopen(file_name[i], "rt");
				fseek(fIn[i], offsetOfKey, SEEK_CUR);
			}
		}

		fDec = fopen("shippriority.fjl", "rt");
		fseek(fDec, 2 * offsetOfKey, SEEK_CUR);

		for (int i = 0; i < 4; i++) {
			if (i != 2) {
				fread(buffer, sizeof(int), 1, fIn[i]);
				result[i] = atoi(buffer);
			}
		}

		fread(buffer, sizeof(int), 1, fDec);
		result2 = atof(buffer);

		cout << "The result of this query is :\n"
			<< "orderkey = " << result[0] << endl
			<< "custkey = " << result[1] << endl
			<< "shippriority = " << result2 << endl
			<< "totalprice = " << result[3] << endl;
	}

	fclose(fIndex);
	fclose(fDec);

	for (int i = 0; i < 4; i++)
		fclose(fIn[i]);

	free(buffer);
}

query::~query() {

}
