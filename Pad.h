//
// Created by dkwhi on 9/10/2017.
//

#ifndef EXAMPLES_PAD_H
#define EXAMPLES_PAD_H

#include "pFlag.h"

class Pad{
public:

    Pad(){}
    Pad(pFlag* flag){
        padProcess(flag->getUnpad(), flag->getN());
    }
    ~Pad(){}

    int getPadError();

private:

    int padError;
    void padProcess(bool unpad, int n);
};
#endif //EXAMPLES_PAD_H
