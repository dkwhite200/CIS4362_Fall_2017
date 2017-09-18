//
// Created by dkwhi on 8/29/2017.
//

#include "Disp.h"
#include <iostream>
#include <cstddef>
#include <sstream>

//returns the error code for the return value of main
int Disp::errorHandler() {
    switch (dispError){
        case 0:
            return 0;

        case 3:
            std::cerr << "disp ERROR (Type  3): Internal Flag Error is Invalid";
            return 3;

        case 4:
            std::cerr << "disp ERROR (Type 4): Input character is not a hexadecimal digit";
            return 4;

        default:
            std::cerr << "disp ERROR (Type 99): Unexpected Error";
            return 99;
    }
}

//Switches between different flag processes
void Disp::flagHandler(dFlags* flags) {
    switch (flags->getFlags()){
        case 0:
            bin_xout();
            break;

        case 1:
            bin_bout();
            break;

        case 2:
            xin_bout();
            break;

        case 3:
            xin_xout();
            break;

        default:
            dispError = 3;
    }
}

//changes input from binary to hex
void Disp::bin_xout(){
    std::stringstream convert;
    char in;
    int bin;
    std::string buffer;
    std::string out;

    int count = 0;
    while(!std::cin.eof()){     //while cin still has input
        if(isprint(std::cin.peek()) || iscntrl(std::cin.peek())){   //If the character is printable, store in char
            std::cin >> std::noskipws >> in;
            convert << std::hex << (int)in;
            convert >> buffer;
            if (buffer.length() == 1){
                buffer.insert(0, "0");
            }
            out += buffer + " ";
            if(count%8 == 7){ out += "\n"; }
            convert.clear();
            count++;
        }
        else {      //If not printable store as hex int
            std::cin >> std::hex >> bin;
            convert << std::hex << bin;
            convert >> buffer;
            out = buffer + " ";
            if(count%8 == 7){ out += "\n"; }
            convert.clear();
            count++;
        }
    }
    std::cout << out;
    dispError = 0;
}

//outputs original input
void Disp::bin_bout(){
    std::string in;
    int num;
    while(!std::cin.eof()){
        if(isprint(std::cin.peek()) || iscntrl(std::cin.peek())){
            std::cin >> std::noskipws >> in;
            std::cout << in;
        }
        else {
            std::cin >> num;
            std::cout << num;
        }
    }
    dispError = 0;
}

//turns hex input into binary output
void Disp::xin_bout(){
    int in;
    std::stringstream convert;
    std::string buffer;
    int num;
    std::string out;

    while(!std::cin.eof()){         //while there is input in cin
        std::cin >> buffer;
        for (char i : buffer){      //Checks is input is hex
            if(!testHex(i)) {
                dispError = 4;
                return;
            }
        }
        convert << buffer;
        convert >> std::hex >> num;
        out += (char)num;
        convert.clear();
    }

    std::cout << out;
    dispError = 0;
}

//turns hex input into formatted hex output
void Disp::xin_xout(){
    std::string in;
    std::string out;

    int count = 0;
    while(std::cin >> in){      //while there is a next string
        for (char i : in) {
            if (!testHex(i)){  //checks that input is hex
                dispError = 4;
                return;
            }
            out += i;
            if (count % 2 == 1) { out += " "; }
            if (count % 16 == 15) { out += "\n"; }
            count++;
        }
        std::cout << out;
    }
}

//checks if a given character is hex
bool Disp::testHex(char c) {
    char hexChar[] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f','A','B','C','D','E','F',' '};
    for (char i : hexChar) {
        if (c == i){ return true; }
    }
    return false;
}