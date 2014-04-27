#include "load.h"
#include <iostream>
#include "fileException.h"
#include "fileOpenException.h" 
int main() {
    try {
        load *l = new load();
    } catch (FileOpenException& f) {
        f.print();
    }
    return 0;
}
