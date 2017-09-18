//
// Created by dkwhi on 8/29/2017.
//

#ifndef DISP_DISP_H
#define DISP_DISP_H

#include "dFlags.h"


class Disp {
public:

    Disp(){}
    Disp(dFlags* flags){
        flagHandler(flags);
    }
    ~Disp(){}

    int errorHandler();
private:

    int dispError;

    void flagHandler(dFlags* flags);
    void bin_xout();
    void bin_bout();
    void xin_bout();
    void xin_xout();
    bool testHex(char hex);
};


#endif //DISP_DISP_H
