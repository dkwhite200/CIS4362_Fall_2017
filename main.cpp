// Main function for pad.exe
// Created by dkwhi on 9/10/2017.
//
#include <iostream>
#include "pFlag.h"
#include "Pad.h"

int main(int argc, char* argv[]){
    pFlag* flag = new pFlag(argc, argv);
    if (flag->getFlagError() != 0){ return flag->getFlagError(); }
    Pad pad(flag);
    return pad.getPadError();
}


