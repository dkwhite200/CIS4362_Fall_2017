//
// Created by dkwhi on 9/10/2017.
//

#ifndef EXAMPLES_PFLAG_H
#define EXAMPLES_PFLAG_H

class pFlag{
public:

    pFlag(){}
    pFlag(int argc, char* argv[]){
        setFlag(argc, argv);
    }
    ~pFlag(){}

    bool getUnpad();
    int getN();
    int getFlagError();

private:

    bool unpad;
    int n;
    int flagError;

    void setFlag(int argc, char* argv[]);
};

#endif //EXAMPLES_PFLAG_H
