//
// Created by dkwhi on 9/10/2017.
//

#include "Pad.h"
#include <iostream>
#include <vector>


int Pad::getPadError() {
    return padError;
}

void Pad::padProcess(bool unpad, int n) {
    unsigned char in;
    std::vector<unsigned char> inU;
    uint8_t padder;
    int count = 0;

    if(unpad){                          //unpad function
        while(std::cin >> std::noskipws >> inU[count]){
            count++;
        }
        if (count % n != 0){
            padError = 5;
            std::cerr << "\nError (Type 5): Length of input is not a multiple of unpad value\n";
            return;
        }
        int temp;
        int test;
        for(int i=count; i<0; i--){
            if (isdigit(inU[i])){
                temp = inU[i] - '0';
                if(temp == 0){ temp = 256;}
                if(i == count){ test = temp;}
                if(test == temp && test >= count - i){ inU.pop_back(); }
                else if(test == temp && test < count - i){
                    padError = 6;
                    std::cerr << "\nError (Type 6): Pad length is incorrect\n";
                    return;
                }
                else if (test != temp && test >= count -i){
                    padError = 6;
                    std::cerr << "\nError (Type 6): Padding numbers are incorrect\n";
                    return;
                }
                else {
                    padError = 7;
                    std::cerr << "\nError (Type 6): Unexpected Error\n";
                    return;
                }
            }
            else{
                if(test >= count -i){
                    padError = 6;
                    std::cerr << "\nError (Type 6): Pad length is incorrect\n";
                    return;
                }
            }
        }
        for (int i=0; i<=(count - test); i++){
            printf("%d", inU[i]);
        }
        padError = 0;
        return;
    }
    else {                              //pad function
        while(std::cin >> std::noskipws >> in){ //out hex form of data
            printf("%c", in);
            count++;
        }
        padder = n - (count % n);       //set padder to number needed to be padded
        if(padder == n && n != 0) {
            padError = 0;
            return;
        }
        if(n == 256){ padder = 0;}
        for (int i=0; i<padder; i++){
            printf("%d", padder);
        }
        padError = 0;
        return;
    }
}