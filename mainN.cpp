#include <iostream>
#include "nFlags.h"
#include "Nsub.h"

int main(int argc, char* argv[]) {

    nFlags* flag = new nFlags(argc, argv);
    if (flag->checkError() != 0){
        return flag->checkError();
    }
    Nsub nsub(flag);
    return nsub.checkErrors();
}