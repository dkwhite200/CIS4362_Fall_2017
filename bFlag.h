#ifndef EXAMPLES_BFLAG_H
#define EXAMPLES_BFLAG_H

#include <vector>

class bFlag{
public:

	bFlag(){}
	bFlag(int argc, char* argv[]){
		flagHandler(argc, argv);
	}
	~bFlag(){}
	
	bool encrypt;
	int flagError;
	int n;
	std::vector<int> key;
	
	bool getEncrypt();
	int getFlagError();
	int getN;
	std::vector<int> getKey();
	
private:
	
	void flagHandler(int argc, char* argv[]);
	void makeKey(string file);

}

#endif //EXAMPLES_FLAGB_H
