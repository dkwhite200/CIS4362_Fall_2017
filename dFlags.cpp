//
// Created by dkwhi on 8/29/2017.
//

#include <iostream>
#include "dFlags.h"

//Returns flagCode
int dFlags::getFlags() {
    return flagCode;
}
//Returns Errors
int dFlags::checkErrors() {
    return flagError;
}

//This Function sets the flag codes and possible flag errors. 0's are defaults/normal operation
void dFlags::makeFlags() {
    flagCode = 0;
    flagError = 0;
}
void dFlags::makeFlags(int argc, char *args[]) {
    if (argc < 1 || argc > 3){      //Error throw
        flagError = 1;
        std::cerr << "disp ERROR (Type 1): Too Many Flags\n";
        return;
    }
    if (argc == 1){    //Default Option, No flags
        flagCode = 0;
        flagError = 0;
    }
    else if (argc == 2){    //One flag is picked
        std::string flg = args[1];
        if (flg == "-bin" || flg == "-xout"){   //Defaults selected
            flagCode = 0;
        }
        else if(flg == "-bout"){    //(bin, bout)
            flagCode = 1;
        }
        else if(flg == "-xin") {    //(xin, xout)
            flagCode = 3;
        }
        else {                      //Error throw
            flagError = 2;
            std::cerr << "disp ERROR (Type 2): Flag Not Valid\nAvailable Flags: (-bin, -xin, -bout -xout)\n";
            return;
        }
        flagError = 0;
    }
    else {              //Two Flags are picked
        std::string flg1 = args[1];
        std::string flg2 = args[2];
        if ((flg1 == "-bin" && flg2 == "-xout") || (flg1 == "-xout" && flg2 == "-bin")){   //Defaults selected
            flagCode = 0;
        }
        else if((flg1 == "-bin" && flg2 == "-bout") || (flg1 == "-bout" && flg2 == "-bin")){    //(bin, bout)
            flagCode = 1;
        }
        else if((flg1 == "-xin" && flg2 == "-bout") || (flg1 == "-bout" && flg2 == "-xin")){    //(xin, bout)
            flagCode = 2;
        }

        else if((flg1 == "-xin" && flg2 == "-xout") || (flg1 == "-xout" && flg2 == "-xin")) {    //(xin, xout)
            flagCode = 3;
        }
        else {                      //Error throw
            flagError = 2;
            std::cerr << "disp ERROR (Type 2): Flag Not Valid\nAvailable Flags: (-bin, -xin, -bout -xout)\n";
            return;
        }
        flagError = 0;
    }
}