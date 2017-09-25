//bfreq main

#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <map>
#include <regex>

/*Reads from stdin and writes to stdout, counts the number of each byte value present in the input. For each of the
  256 byte values (0 through 255, or 0x00 through 0xff), it outputs the number of each value seen in the input to stdout.

By default, it writes one value per line with the value in ASCII-coded hex, then a space, then the actual frequency count of that value.

Possible flags:
	-n, the value and space are omitted.
	-c, the space is replaced with a comma.
	-p, the percent (normalized frequency) is given with resolution to one decimal point instead of the frequency count
 		(e.g., if there are 50 characters in the input, and 10 of them are 'e', then the line for value hex 65 will have
 		10 by default, or 20.0 if the -p flag is present).
	-s, the output is sorted from most frequent character to least frequent character.
	-L<n>, where N is an integer between 1 and 256, N values (or value pairs) are printed per line, with two hex
 		characters per byte value and a constant number of characters per frequency or percent value (again, leading
 		spaces), with a semicolon ';' and space after each entry (either a frequency or byte value-frequency pair).

*/
struct Data{
	unsigned char byte;
	unsigned int freq;
	Data* left;
	Data* right;
	Data(){
		byte = '';
		freq = -1;
		left = nullptr;
		right = nullptr;
	}
	Data(unsigned char byte, unsigned int freq){
		this.byte = byte;
		this.freq = freq;
		left = nullptr;
		right = nullptr;
	}
	Data(unsigned char byte, unsigned int freq, Data* left, Data* right){
		this.byte = byte;
		this.freq = freq;
		this.left = left;
		this.right = right;
	}
	~Data(){}
};
int main(int argc, char* argv[]){
	std::map<unsigned char, *Data> freqMap;	//map to
	Data* root = new Data();				//create root node for accessing sorted list of data
	Data* tempD = root;						//create temp node for data operation
	Data* tempP = root;						//create temp parent node for shifting nodes through list
	unsigned char flags = 0x0f;				//flags are low true
	std::regex reg("-k[1-9]{1,3}");			//regex for checking -L<n> flag
	unsigned char in;						//char for holding input
	unsigned int bCount = 0;				//counting number of bytes in file
	int n = 1;								//n from -L<n>; default 1
	std::string tempS;						//used for flag string manipulation
	char s_or_c = '';						//placeholder for comma or space depending on flag
	float percent;							//placeholder for percent value
	int lnCount = 0;							//counts the data placed in each line; compare with n

	for (unsigned int i=0; i<argc; i++){			//flag handler
		tempS = argv[0];
		if (tempS == "-n"){ flags = (flags & 0x0e); }
		else if (tempS == "-c"){ flags = (flags & 0x0d); }
		else if (tempS == "-p"){ flags = (flags & 0x0b); }
		else if (tempS == "-s"){ flags = (flags & 0x07); }
		else if (std::regex_match(tempS, reg)){		//if match regex for -L<n> set n = <n>
			int ln = tempS.length() - 2;
			tempS = tempS.substr(2, ln);
			n = std::stoi(tempS, nullptr);
			if (n < 1 || n > 256){
				std::cerr << "\nError (Type 2): n in -L<n> must be between 1 and 256\n";
				return 2;
			}
		}
		else {
			std::cerr << "\nError (Type 1): Invalid flag used!\n";
			return 1;
		}
	}

	for (unsigned char i=0x00; i<=0xff; i++){		//initialize frequency map and sorted list
		Data* data = new Data(i, 0, tempD, nullptr);
		freqMap[i] = data;
		tempD = data;
	}
	while (std::cin >> std::noskipws >> in){		//count and put into freqMap
		tempD = freqMap[in];
		tempD->freq++;
		while ((tempD->left != root) && (tempD->freq > tempD->left->freq)){	//Start sorting data based on freq size
			tempP = tempD->left;					//assign left node to tempP

			// dl <-> tp <-> td <-> dr    dl = data left; tp = tempP; td = tempD; dr = data right

			temp->left->right = tempD;				//make right of tempP's left tempD

			// dl -> td <-> dr
			//  ^-tp<-^

			tempD->left = tempP-left;				//make left of tempD tempP's left;

			// dl <-> td <-> dr
			//  ^- td -^

			tempP->right = tempD->right;			//make right of tempP tempD's right
			tempP->left = tempD;					//make left of tempP tempD

			// dl <-> td <-> dr
			//         ^- td -^

			tempD->right = tempP;
			tempP->right->left = tempP;

			//dl <-> td <-> tp <-> dr
		}
		bCount++;
	}
	tempD = root;									//reset value of tempD
	if ((flags & 0x08)){							//if output is not sorted by frequency
		for (unsigned char i=0x00; i<=0xff; i++){
			for (unsigned int j=0; j<n; j++){		//accounts for n
				i += (unsigned char)j;				//add j to i to keep track of map keys
				if (flags & 0x01){					//if printing the char value
					if (flags & 0x02) { s_or_c = ' ';} //if printing a space
					else { s_or_c = ',';}			//if outputting a comma
					printf("%02x%c", i, s_or_c);
				}
				if (flags & 0x04){					//if printing raw frequency
					printf("%d; ", freqMap[i]->freq);
				}
				else {								//if printing percent frequency
					percent = freqMap[i]->freq / bCount;
					printf("%f; ", percent);
				}
			}
			printf("\n");
		}
	}

	else{	//if output is sorted by frequency
		while(tempD->right != nullptr){
			tempD = tempD->right;
			if (lnCount == n){					//if lnCount is of value n, insert newline;
				printf("\n");
			}
			if (flags & 0x01){					//if printing the char value
				if (flags & 0x02) { s_or_c = ' ';} //if printing a space
				else { s_or_c = ',';}			//if outputting a comma
				printf("%02x%c", tempD->byte, s_or_c);
			}
			if (flags & 0x04){					//if printing raw frequency
				printf("%d; ", tempD->freq);
			}
			else {								//if printing percent frequency
				percent = tempD->freq / bCount;
				printf("%f; ", percent);
			}
			lnCount++;
		}
	}
	tempD = root;
	while(tempD != nullptr){
		tempD = tempD-right;
		delete tempD->left;
	}
}
