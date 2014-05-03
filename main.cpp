#include <stdio.h>
#include "string.h"
#include "load.h"
#include "query.h"
#include "fileException.h"
#include "fileOpenException.h"


int main(int argc, char* argv[]) {
	if (argc != 3) {
		printf("Illegal command!\n");
		return 0;
	}
    if(strcmp(argv[1],"load") == 0) {
        if(strcmp(argv[2], "orders") == 0) {
            try {
                load *l = new load();
                delete l;
            } catch (FileException& f) {
                f.print();
            }
        } else {
            printf("Only orders can be loaded!\n");
        }


    }
    else if (strcmp(argv[1], "retrieve") == 0) {
        if (strcmp(argv[2], "orders") == 0) {
            int orderkey_ = 0;
            while (scanf("%d", &orderkey_) != EOF) {
                try {
                    query *q = new query(orderkey_);
                    delete q;
                } catch (FileException& f) {
                    f.print();
                }
            }
        } else {
            printf("Only orders can be queried!\n");
        }
    } else {
        printf("Illegal command!\n");
    }
    return 0;
}
