//
// Created by dkwhi on 8/29/2017.
//

#ifndef DISP_FLAGS_H
#define DISP_FLAGS_H


class dFlags {
public:

    dFlags(){
        makeFlags();
    }
    dFlags(int argc, char* args[]){
        makeFlags(argc, args);
    }
    ~dFlags(){}

    int getFlags(); //Returns Flag codes
    int checkErrors();  //Returns Error codes

private:

    int flagCode;   //[0-3]: 0 = default(bin, xout); 1 = (bin, bout); 2 = (xin, bout); 3 = (xin, xout)
    int flagError;  //[0-2]: 0 = no error; 1 = "Too many Flags"; 2 = "Wrong Flag Name"
    void makeFlags();   //This Function sets the flag codes and possible flag errors. 0's are defaults/normal operation
    void makeFlags(int argc, char* args[]);
};


#endif //DISP_FLAGS_H
