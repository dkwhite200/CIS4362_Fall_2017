//
// Created by dkwhi on 9/1/2017.
//

#include "nFlags.h"
#include <fstream>
#include <sstream>
#include <algorithm>

int nFlags::checkError(){
    return flagError;
}

std::string nFlags::getKey() {
    return key;
}

void nFlags::flagHandler() {
    key = "01 23 45 67 89 ab cd ef";
    flagError = 0;
}
void nFlags::flagHandler(int argc, char* argv[]) {
    bool decrypt = false;
    bool xin = false;
    std::string file;
    std::string temp;
    if (argc < 3 || argc > 5){
        flagError = 1;
        std::cerr << "nsub ERROR (Type 1): Too many nsub arguments.\n";
        return;
    }

    for (int i=0; i<argc; i++ ){

        temp = argv[i];
        if (temp == "-e" || temp == "-b"){}
        else if(temp == "-d"){ decrypt = true; }
        else if (temp == "-x"){ xin = true; }
        else if (temp == "-k"){
            file = argv[i+1];
            i++;
        }
        else {
            flagError = 2;
            std::cerr << "nsub ERROR (Type 2): Invalid flag used.\n";
            return;
        }
    }
    fileHandler(decrypt, xin, file);
}
void nFlags::fileHandler(bool decrypt, bool xin, std::string file) {
    std::fstream fs(file, std::fstream::in | std::fstream::out);
    if(!fs.is_open()){
        flagError = 3;
        std::cerr << "nsub ERROR (Type 3): Key file not found.\n";
        return;
    }

    if(!decrypt && !xin){ bin_encrypt(fs); }
    else if (decrypt && !xin){ bin_decrypt(fs); }
    else if (!decrypt && xin){ xin_encrypt(fs); }
    else { xin_decrypt(fs); }

    fs.close();
    keyCheck();
}

void nFlags::bin_encrypt(std::fstream &fs) {
    char in;
    int bin;
    std::stringstream convert;
    std::string buffer;

    while(!fs.eof()){     //while cin still has input
        if(isprint(fs.peek()) || iscntrl(fs.peek())){   //If the character is printable, store in char
            fs >> std::noskipws >> in;
            convert << std::hex << (int)in;
            convert >> buffer;
            if (buffer.length() == 1){ buffer.insert(0, "0"); }
            key += buffer;
            convert.clear();
        }
        else {      //If not printable store as hex int
            std::cin >> std::hex >> bin;
            convert << std::hex << bin;
            convert >> buffer;
            key = buffer;
            convert.clear();
        }
    }
}
void nFlags::bin_decrypt(std::fstream &fs) {
    char in;
    char temp;
    int bin;
    std::stringstream convert;
    std::string buffer;

    while(!fs.eof()){     //while cin still has input
        if(isprint(fs.peek()) || iscntrl(fs.peek())){   //If the character is printable, store in char
            fs >> std::noskipws >> in;
            convert << std::hex << (int)in;
            convert >> buffer;
            if (buffer.length() == 1){ buffer.insert(0, "0"); }
            temp = buffer[1];
            buffer[1] = buffer[0];
            buffer[0] = temp;
            key.insert(0, buffer);
            convert.clear();
        }
        else {      //If not printable store as hex int
            std::cin >> std::hex >> bin;
            convert << std::hex << bin;
            convert >> buffer;
            std::reverse(buffer.begin(), buffer.end());
            key = buffer;
            convert.clear();
        }
    }
}
void nFlags::xin_encrypt(std::fstream &fs) {
    std::string in;
    std::string out;

    while(fs >> in){      //while there is a next string
        for (char i : in) {
            if (!testHex(i)){  //checks that input is hex
                flagError = 4;
                std::cerr << "nsub ERROR (Type 4): Input contains a non-hexidecimal character.\n";
                return;
            }
            key += i;
        }
    }
}
void nFlags::xin_decrypt(std::fstream &fs) {
    std::string in;
    std::string temp;

    while(fs >> in){      //while there is a next string
        for (char i : in) {
            if (!testHex(i)){  //checks that input is hex
                flagError = 4;
                std::cerr << "nsub ERROR (Type 4): Input contains a non-hexidecimal character.\n";
                return;
            }
            temp = i;
            key.insert(0, temp);
        }
    }
}

void nFlags::keyCheck() {
    if (!(key.length() == 16)){
        flagError = 5;
        std::cerr << "nsub ERROR (Type 5): Key must contain only 16 nibbles.\n";
        return;
    }
    if (testRepeats()){
        flagError = 6;
        std::cerr << "nsub ERROR (Type 6): Invalid.\n";
        return;
    }
}
bool nFlags::testHex(char c) {
    char hexChar[] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f','A','B','C','D','E','F'};
    for (char i : hexChar) {
        if (c == i){ return true; }
    }
    return false;
}
bool nFlags::testRepeats(){
    for (int i=0; i<key.length(); i++){
        for (int j=0; j>i; j--){
            if (key[i] == key[j]){ return false; }
        }
    }
}