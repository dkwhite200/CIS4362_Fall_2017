//bfreq main

#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <map>
#include <regex>

/*reads from stdin and writes to stdout, counts the number of each byte value present in the input. For each of the 256 byte values (0 through 255, or 0x00 through 0xff), it outputs the number of each value seen in the input to stdout.

By default, it writes one value per line with the value in ASCII-coded hex, then a space, then the actual frequency count of that value.

Possible flags:
	-n, the value and space are omitted.
	-c, the space is replaced with a comma.
	-p, the percent (normalized frequency) is given with resolution to one decimal point instead of the frequency count (e.g., if there are 50 characters in the input, and 10 of them are 'e', then the line for value hex 65 will have 10 by default, or 20.0 if the -p flag is present).
	-s, the output is sorted from most frequent character to least frequent character.
	-L<n>, where N is an integer between 1 and 256, N values (or value pairs) are printed per line, with two hex characters per byte value and a constant number of characters per frequency or percent value (again, leading spaces), with a semicolon ';' and space after each entry (either a frequency or byte value-frequency pair).

*/
struct data{
	
}
int main(int argc, char* argv[]){
	std::map<unsigned char, unsigned int> freqMap;
	unsigned char flags = 0x0f;	//flags are low true
	std::regex reg("-k[1-9]{1,3}");
	unsigned char in;
	unsigned int bCount = 0;
	int n = 1;
	std::string temp;
	char s_or_c = '';
	float percent;

	for (unsigned int i=0; i<argc; i++){	//flag handler
		temp = argv[0];
		if (temp == "-n"){ flags = (flags & 0x0e); }
		else if (temp == "-c"){ flags = (flags & 0x0d); }
		else if (temp == "-p"){ flags = (flags & 0x0b); }
		else if (temp == "-s"){ flags = (flags & 0x07); }
		else if (std::regex_match(temp, reg)){
			int ln = temp.length() - 2;
			temp = temp.substr(2, ln);
			n = std::stoi(temp, nullptr);
			if (n < 1 || n > 256){
				std::cerr << "\nError (Type 2): n in -L<n> must be between 1 and 256\n"
				return 2;
			}
		}
		else {
			std::cerr << "\nError (Type 1): Invalid flag used!\n"
			return 1;
		}
	}

	for (unsigned char i=0x00; i<=0xff; i++){	//initialize frequency map
		freqMap[i] = 0;
	}
	while (std::cin >> std::noskipws >> in){	//count and put into freqMap
		freqMap[in]++;
		bCount++;
	}

	if ((flags & 0x08)){	//if output is not sorted by frequency
		for (unsigned char i=0x00; i<=0xff; i++){
			for (unsigned int j=0; j<n; j++){	//accounts for n
				i += (unsigned char)j;	//add j to i to keep track of map keys
				if (flags & 0x01){	//if printing the char value
					if (flags & 0x02) { s_or_c = ' '} //if printing a space
					else { s_or_c = ','}	//if outputting a comma
					printf("%02x%c", i, s_or_c);
				}
				if (flags & 0x04){	//if printing raw frequency
					printf("%d; ", freqMap[i]);
				}
				else {	//if printing percent frequency
					percent = freqMap[i] / bCount;
					printf("%f; ", percent);
				}
			}
			printf("\n");
		}
	}

	else{	//if output is sorted by frequency
		for
	}
}
