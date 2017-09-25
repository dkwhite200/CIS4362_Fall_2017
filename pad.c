#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

//for unpad and pad
#define MAXBYTES 16
#define DEFAULT_LENGTH 8
#define DEFAULT_BLENGTH 8
#define MAX_LENGTH 256

//for unpad

#define E_NOT_BLOCK_MULTIPLE 1
#define E_BAD_LAST_PAD_BYTE 2
#define E_PAD_BYTES_NOT_SAME 3


char buffer[MAX_LENGTH];
int blength = DEFAULT_LENGTH;

char hexchar[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c','d', 'e', 'f'};

int main(int argc, char** argv)
{
    int c,  pad_char;
    int pmode = 1; 
    int pad_length, remainder;
//    int un, ln;
    int count=0;


// begin command line processing
 if (argc < 1) {
        fprintf(stderr, "error: too few args\n");
        //fprintf(stderr, USAGE);
        return 1;
    }
    for (count = 1; count < argc; ++count) {
        if (argv[count][0] != '-') {
		// default is -p for pad and -b 8
		//	pmode = 1;
		//blength=8;
        }
	else {
        switch (argv[count][1]) {
            case 'p':  { // pad
                pmode = 1;
                break;
            }
            case 'u': {  // unpad
                pmode = 0;
                break;
            }
            case 'b': {
                //if (DEBUG) fprintf(stderr, "Block length %s\n", &argv[count][2]);
                sscanf(&argv[count][2],"%d", &blength);
                // another space sscanf(&argv[count][2],"%d", &blength);

                break;
            }
            default: {
                break;
            }
        }
	} // end else
    }   // end for - commandline flag processing




 if (pmode == 1) {  // pad by default
count = 0;
// Read in block size, by Steve
    while ((c = getchar()) != EOF) 
    {
	// copy input to output
	putchar(c);
	++count;
    }
//	printf("This is blength: %d \n ", blength);
    remainder = count % blength;    
    pad_length = blength - remainder;
    pad_char = (pad_length == 0) ? blength : pad_length;

    for (count = 0; count < pad_char; ++count) {
    	putchar(pad_char);
    }
    return 0;
}



// else if pmode = 0 do this
else {
//    int un, ln;
    int count=0;

    c = getchar();      // get first char
    while (c != EOF)
    {
        // un = c >> 4;
        // ln = c & 0xf;
        // putchar(hexchar[un]);
        // putchar(hexchar[ln]);

        // copy input to buffer in case it contains padding
        buffer[count] = c;

        c = getchar();  // get next char
        if ((++count % blength) == 0) { // buffer full
            if (c != EOF) {             // not last block
                for (count = 0; count < blength; ++count) {
                    // copy block to stdout
                    putchar(buffer[count]);
                }
                // Steve added
                count = 0;
                //steve added
            }
            else {      // last block
                        // last value in block is pad length
                pad_length = buffer[blength-1];
                if ((pad_length <= 0) || (pad_length > blength)) {
                        // bad pad length value
                    fprintf(stderr, "Bad pad: last byte value = %d\n",
                                                        pad_length);
                    return(E_BAD_LAST_PAD_BYTE);
                }
                else {  // last byte looks OK
                        // check rest of pad bytes
                    for (count = 1; count < pad_length; ++count) {
                        if (buffer[blength-1-count] != pad_length) {
                                // pad byte does not match pad length
                            fprintf(stderr, "Bad pad byte: pad length = %d, byte %d = %d\n", pad_length, count, buffer[blength-1-count]);
                            return( E_PAD_BYTES_NOT_SAME );
                        }
                    }   // pad bytes all match
                        // output data bytes from buffer
                    for (count = 0; count < blength-pad_length; ++count) {
                        putchar(buffer[count]);
                    }   // done outputting last partial block
                }   // done with final block with good pad
            }
        }  // done with processing a full block
        else {  // not a full block
            if (c == EOF) {     // partial last block
                fprintf(stderr, "File length not multiple of block size: partial block length = %d\n", count);
                return( E_NOT_BLOCK_MULTIPLE);
            }
        }
    }   // done with input

    return 0;
}


} // end program
