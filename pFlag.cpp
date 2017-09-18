//
// Created by dkwhi on 9/10/2017.
//

#include "pFlag.h"
#include <iostream>
#include <regex>

bool pFlag::getUnpad() {
    return unpad;
}

int pFlag::getN() {
    return n;
}

int pFlag::getFlagError() {
    return flagError;
}

//This method initialises the class variables unpad, n and flagError
void pFlag::setFlag(int argc, char* argv[]) {
    n = 8;
    regex reg("-b/d{1,3}");          		//create regex to check for block number flag
    if(argc < 1 || argc > 3){               //check number of arguments
        flagError = 1;
        std::cerr << "\nError (Type 1): Invalid number of arguments passed.\n";
        return;
    }

    for (int i=1; i<argc; i++){    			//check each flag
        if (argv[i] == "-p"){
            if(unpad == true){
                flagError = 2;
                std::cerr << "\nError (Type 2): Invalid flag used. Cannot have -p and -u flags active.\n";
                return;
            }
            unpad = false;
        }
        if (argv[i] == "-u"){
            if(unpad == false) {
                flagError = 2;
                std::cerr << "\nError (Type 2): Invalid flag used. Cannot have -p and -u flags active.\n";
            }
            unpad = true;
        }
        else if (regex_match(argv[i],reg)){ //if block number is found, parse out and store in n
            std::string temp = argv[i];
            unsigned int ln = temp.length() - 2;
            n = std::stoi(temp.substr(2,ln));
        }
        else {
            flagError = 2;
            std::cerr << "\nError (Type 2): Invalid flag used.\n";
            return;
        }
    }
    if(n < 1 || n > 256){
        flagError = 4;
        std::cerr << "\nError (Type 4): n is not within bounds (i.e. 1 < n <= 256)\n";
    }
    flagError = 0;
}
