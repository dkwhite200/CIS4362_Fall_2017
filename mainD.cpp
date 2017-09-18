#include <iostream>
#include "dFlags.h"
#include "Disp.h"
using namespace std;

int main(int argc, char* args[]) {
    dFlags* flags = new dFlags(argc, args);
    if(flags->checkErrors() > 0){
        return flags->checkErrors();
    }
    Disp disp(flags);
    return disp.errorHandler();
}
