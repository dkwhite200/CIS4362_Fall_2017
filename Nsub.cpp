//
// Created by dkwhi on 9/1/2017.
//

#include "Nsub.h"
#include <iostream>
#include <sstream>


int Nsub::checkErrors() {
}

void Nsub::getPlainText() {
    std::stringstream convert;
    char in;
    int bin;
    std::string buffer;
    std::string out;

    while(!std::cin.eof()){     //while cin still has input
        if(isprint(std::cin.peek()) || iscntrl(std::cin.peek())){   //If the character is printable, store in char
            std::cin >> std::noskipws >> in;
            convert << std::hex << (int)in;
            convert >> buffer;
            if (buffer.length() == 1){
                buffer.insert(0, "0");
            }
            plainText += buffer;
            convert.clear();
        }
        else {      //If not printable store as hex int
            std::cin >> std::hex >> bin;
            convert << std::hex << bin;
            convert >> buffer;
            plainText = buffer;
            convert.clear();
        }
    }
    nsubError = 0;
}
void Nsub::getCipherText() {
    int keyNibble;
    std::string temp;

    for (char i : plainText){
        temp = i;
        keyNibble = (int)strtol(temp, NULL, 16);
        std::cout << (int)key[keyNibble];
    }
}
