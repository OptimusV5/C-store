#include "load.h"
#include <cstdio>

int main() {
    try {
        load *l = new load();
    } catch (FILE*) {
        printf("File orders.tbl not found!\n");
    }
    return 0;
}
