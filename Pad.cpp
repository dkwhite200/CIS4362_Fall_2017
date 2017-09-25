//
// Created by dkwhi on 9/10/2017.
//

#include "Pad.h"
#include <iostream>
#include <vector>
#include <cstdint>


int Pad::getPadError() {
    return padError;
}

void Pad::padProcess(bool unpad, int n) {
    unsigned char in;
    std::vector<unsigned char> inU;
    uint8_t padNum;
    unsigned char padder;
    int count = 0;
    
//unpad function
    if(unpad){                          
        while(std::cin >> std::noskipws >> in){
			inU.push_back(in);
            count++;
        }
        if (count % n != 0){			//error if file is not of block n
            padError = 5;
            std::cerr << "\nError (Type 5): Length of input is not a multiple of unpad value\n";
            return;
        }
        int temp;						//create temp for number pad int holding
        int test;						//create test int for testing pad is same number
        for(int i=count; i<0; i--){		//iterate back in inU untill pad is gone
            
            temp = (int)inU[i];			//set temp to hex value of inU[i]
            if(temp == 0){ temp = 256;}	//set temp to 0 if 256
            if(i == count){ test = temp;}//initialize test condition of same pad number
            if(test == temp){
				if(test >= (count - i)){ inU.pop_back(); }//pop out pad if all seems well
				else {					//error if pad ends before it should
					padError = 6;
					std::cerr << "\nError (Type 6): Pad length is incorrect\n";
					return;
				}
            }
            else if(test != temp){ 
				 
				if(test < (count - i)){ break;}//break if int is not pad # and after padding
				else{					//error if pad number changes before it should
					padError = 6;
					std::cerr << "\nError (Type 6): Padding numbers are incorrect\n";
					return;
				}
            }
            else {						//unhandled errors
				padError = 7;
				std::cerr << "\nError (Type 6): Unexpected Error\n";
				return;
            }					
        }
        
        for (int i=0; i<=(count - test); i++){//print data to stdout
            printf("%c", inU[i]);
        }
        padError = 0;
        return;
    }
    
//pad function
    else {                              	
        while(std::cin >> std::noskipws >> in){ //print data
            printf("%c", in);
            count++;
        }
        padNum = n - (count % n);       //set padder to number needed to be padded
        if(padNum == n && n != 0) {
            padError = 0;
            return;
        }
        if(n == 256){ padNum = 0;}		//set pad to 0 if n = 256
        for (int i=0; i<padNum; i++){	//print padding
			padder = (char)padNum;
            printf("%c", padder);
        }
        padError = 0;
        return;
    }
}
