#include "bFlag.h"
#include <fstream>

bool bFlag::getEncrypt(){
	return encrypt;
}


int bFlag::getFlagError(){
	return falgError;
}


int bFlag::getN(){
	return n;
}


std::vector<int> bFlag::getKey(){
	return key;
}


void bFlag::flagHandler(int argc, char* argv[]){
	n = 8;
    std::regex regN("-b[0-9]{1,3}");         //create regex to check for block number flag
    if(argc < 3 || argc > 5){               //check number of arguments
        flagError = 1;
        std::cerr << "\nError (Type 1): Invalid number of arguments passed.\n";
        return;
    }

    for (int i=1; i<argc; i++){    			//check each flag
		std::string temp = argv[i];
        if (temp == "-e"){ encrypt = true; }
        else if (temp == "-d"){ encrypt = false; }
        else if (temp == "-k"){
			std::string = agrv[i+1];
			makeKey(file);
			i++;
		}
        else if (std::regex_match(temp,reg)){ //if block number is found, parse out and store in n
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
}


void bFlag::makeKey(string file){
	std::fstream fs(file);
	unsigned char in;
	int keyByte;
	while(fs >> in){
		keyByte = in;
		key.push_back(keyByte);
	}
}
