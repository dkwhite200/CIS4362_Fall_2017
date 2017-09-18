//
// Created by dkwhi on 9/1/2017.
//

#ifndef NSUB_NSUB_H
#define NSUB_NSUB_H

#include "nFlags.h"

class Nsub {
public:

    Nsub(){}
    Nsub(nFlags* flag){
        key = flag->getKey();
        getPlainText();
        getCipherText();
    }
    ~Nsub(){}

    int checkErrors();

private:
    int nsubError;
    std::string key;
    std::string plainText;
    std::string cipherText;

    void getPlainText();
    void getCipherText();

};


#endif //NSUB_NSUB_H
