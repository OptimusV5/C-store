#ifndef QUERY
#define QUERY

#include <cstdio>

using namespace std;

class query {
public:
	query(int orderid);

	virtual void Query();			//query main function
	virtual int falseBinSerach();
	virtual int trueBinSerach();
	virtual void LocatePage();		//find orderkey in which page
	virtual void LocateOrderkey();	//find orderkey in which location
	~query();

private:
	int orderkey;					//store the target orderkey
	int numOfPage;					//store the number of Pages
	int offsetOfKey;				//store the offset of keys
	int result[4];					//store the result of query
	double result2;

	int *page_int;				//store orderkey

	FILE *fIndex;					//open index.fjl
	FILE *fIn[4];					//open orderkey, custkey, totalprice's .fjl
	FILE *fDec;						//open shippriority.fjl

	char file_name[4][20];	//fourkey's name
	
};

#endif
