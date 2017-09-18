//
// Created by dkwhi on 9/1/2017.
//

#ifndef NSUB_NFLAGS_H
#define NSUB_NFLAGS_H

#include <iostream>


class nFlags {
public:

    nFlags(){
        flagHandler();
    }
    nFlags(int argc, char* argv[]){
        flagHandler(argc, argv);
    }
    ~nFlags(){}

    int checkError();
    std::string getKey();

private:

    std::string key;
    int flagError;

    void flagHandler();
    void flagHandler()(int argc, char* argv[]);
    void fileHandler(bool decrypt, bool xin, std::string file);
    void bin_encrypt(std::fstream &fs);
    void bin_decrypt(std::fstream &fs);
    void xin_encrypt(std::fstream &fs);
    void xin_decrypt(std::fstream &fs);
    void keyCheck();
    bool testHex(char c);
    bool testRepeats();
};


#endif //NSUB_NFLAGS_H
