#include <iostream>
#include "string.h"
#include <stdio.h>
#include "load.h"
#include "query.h"
#include "fileException.h"
#include "fileOpenException.h"

using namespace std;

int main(int argc, char* argv[]) {
    if(strcmp(argv[1],"load") == 0 && argvc == 3) {
        if(strcmp(argv[2],"orders") == 0) {
            try {
                load *l = new load();
            } catch (FileException& f) {
                f.print();
            }
        } else{
            printf("Only orders can be loaded!\n");
        }


    }
    else if(strncmp(argv[1],"retrieve") == 0 && argvc == 4) {
        if(strcmp(argv[2],"orders") == 0) {
            int orderkey_;
            sscanf(argv[4],"%d",&orderkey_);
            try{
                query *q = new query(orderkey_);
            } catch (FileException) {
                f.print();
            }
        } else{
            printf("Only orders can be queried!\n");
        }
        }
    else {
        printf("Illegal command!\n");
        }
    return 0;
}
