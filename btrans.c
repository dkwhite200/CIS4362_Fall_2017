/*
Reads from stdin, writes to stdout. 
Flags: -e for encrypt
	-d for decrypt
	-b<n> for blocksize = n
	-k<filename> for file containing the key
Description:
Reads in binary bytes from stdin, writes in binary to stdout.
Read n bytes (default n=8) and reorder them according to 
the permutation given in the key file, then output that block of bytes in the permuted order. The input file must be a multiple of n bytes or else an error is output to stderr and the last block (with less than n bytes) is not output. 
The key file is n bytes long that encode (in binary) a permutation of n bytes, with one byte per position, and each byte a unique value in the range of 0 to n-1. 
Encryption (-e option):
The permutation is specified by the position of the key byte, so that the ith byte of input block j is the k(i)th byte of output block j, where k(i) is the binary value of the ith byte of the keyfile, and i ranges from 0 to n-1. 
Decryption:
The permutation is the inverse of the permutation for encryption. Hence, the key file must be read in, then the permutation inverted before applying the transposition. 
Error Checking:
The program must check for error conditions (e.g., missing key file, key file not having a valid permutation of n bytes, not having a multiple of n bytes in the input, etc.), and report any error to stderr in a meaningful way, then exit with a non-zero exit code. 
*/

#include <stdio.h>
#include <ctype.h>

#define DEBUG 0
#define USAGE "Usage: block_trans [-{e|d}] [-b<blocksize>] -k<keyfile>\n"
#define MAXBYTES 256
// block lengths here are in bytes, which must be multiplied by 8 to get bits
#define DEFAULT_BLENGTH 8
#define MAX_BLENGTH 32

char hexchar[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c','d', 'e', 'f'};

// key and transpostion location are for bit locations
int key_val[MAXBYTES];		// as read from key file - byte position
int trans_loc[MAXBYTES];	// forward or inverted permutation
int block_count=0;


int transpose(int);
int check_key(int);
int get_bin_key(int, FILE*);
int get_key_file(int, char*);
int get_block(int, int*);
int transpose_block(int, int*);
int output_block(int, int*) ;

int output_block(int blen, int* block) {
    int i=0;

    for (i=0; i < blen; ++i)
	putchar(block[i]);
    return 0;
}

int transpose(int blen) {
    int newblock[blen];
    int rv = 0;

    if (DEBUG) fprintf(stderr,"Starting transpose\n");

    while ((rv = get_block(blen, newblock)) == 0) {
        if (DEBUG) fprintf(stderr,"Block=");
        if (DEBUG) output_block(blen, newblock);
        if (DEBUG) fprintf(stderr,"\n");
	rv = transpose_block(blen, newblock) ;
	if (!rv) output_block(blen, newblock) ;
    }
    return rv;
}

int get_block(int blen, int *block){
    int c=0;
    int i=0;

    if (DEBUG) fprintf(stderr,"Getting block %d\n", block_count);

    while ((c = getchar()) != EOF) 
    {
	block[i] = c;
	if (DEBUG) putchar(block[i]);
	if ((++i % blen) == 0) break;
    }
    if (c == EOF) {
	if (i) {
	    fprintf(stderr,"\nIncomplete block, length=%d\n",i);
	    return (i);
	}
	return (1);
    }
    else return (i % blen);
}

int transpose_block(int blen, int *block) {
    //int i=0;
    int byte=0;
    //int bit = 0;
    int tmp[blen];

    if (DEBUG) fprintf(stderr,"Transposing block %d\n", block_count++);

	// copy block into temp buffer
    for (byte=0; byte<blen; ++byte)
	tmp[byte] = block[byte];
    if (DEBUG) fprintf(stderr, "tmp=");
    if (DEBUG) output_block(blen, tmp);
    if (DEBUG) fprintf(stderr, "\n");

	// zero out block
    for (byte=0; byte<blen; ++byte)
	block[byte] = 0;

	// move bytes to output posn
    for (byte=0; byte<blen; ++byte) {	// for each byte in block
	// put in place
	block[trans_loc[byte]] = tmp[byte];
    }
    return 0;
}

int get_key_file(int len, char *keyfilename) {
	FILE *fd;
	char c=0;

	c++;
	//if (!DEBUG) fprintf(stderr, "In get_key_file, length of key must be blocksize, len = %d, file = %s\n", len, keyfilename);
	fd = fopen(keyfilename,"r");
	if (fd == NULL) {
	    fprintf(stderr, "Unable to open key_file = %s\n", keyfilename);
	    return -1;
	}
	return(get_bin_key(len, fd));
}

int check_key(int len) {
    int i=0;
    int marked[len];

    if (len > MAXBYTES) {
	fprintf(stderr,"Key length too large: %d\n",len);
	return -1;
    }
    for (i=0; i<len; ++i) {
	marked[i] = 0;
    }

    if (DEBUG) fprintf(stderr, "In check_key, len = %d\n", len);

    for (i=0; i<len; ++i) {
	if (DEBUG) fprintf(stderr, "\t%d:\t%d\n", i, key_val[i]);

	if (key_val[i] >= len) {
	    fprintf(stderr,"Key value too large at %d: %d\n",i,key_val[i]);
	    return 5;
	}
	if (marked[key_val[i]]) {
	    fprintf(stderr,"Duplicate key value at %d: %d\n",i,key_val[i]);
	    return 6;
	}
	marked[key_val[i]] = 1;
    }
    return 0;
}
    
int get_bin_key(int length, FILE *keyfiled) {
    int c;
    int i=0;

    if (length > MAXBYTES) {
	fprintf(stderr,"Key length too large: %d\n",length);
	return -1;
    }
    while ((c = fgetc(keyfiled)) != EOF) {
	key_val[i] = c;

	if (DEBUG) {
		fprintf(stderr, "Key[%d] = %d\n", i, c);
	}
	if (++i >= length) break;
    }
    if (i < length ) {
	fprintf(stderr,"Too few values in key file: %d\n",i);
	return -2;
    }
    return check_key(length);
}


int main(int argc, char **argv)
{
    int blength = DEFAULT_BLENGTH;
    int key_present = 0;
    int emode = 1;
    int count;
    int i;

    if (argc < 2) {
	fprintf(stderr, "error: too few args\n");
	fprintf(stderr, USAGE);
	return 1;
    }
    for (count = 1; count < argc; ++count) {

	if (argv[count][0] != '-') {
	    fprintf(stderr, "error: bad flag: %s\n", argv[count]);
	    fprintf(stderr, USAGE);
	    return 2;
	}
	switch (argv[count][1]) {
	    case 'e': {
	        emode = 1;
		break;
	    }
	    case 'd': {
	        emode = 0;
		break;
	    }
	    case 'b': {
		if (DEBUG) fprintf(stderr, "Block length %s\n", &argv[count][2]);
	        sscanf(&argv[count][2],"%d", &blength);
		break;
	    }
	    case 'k': {

		if (argv[count][2] != '\0')  {
		//section to read key with no space

		key_present =1;
		if (DEBUG) fprintf(stderr, "Getting key from %s\n", &argv[count][2]);
	        if ((get_key_file(blength, &argv[count][2]))!=0) return 1;  
		} else {

		//same section to read key with space replaced 2 with 3
		key_present = 1;
		if (DEBUG) fprintf(stderr, "Getting key from %s\n", &argv[count][3]); // used to be [count][3]
	        if ((get_key_file(blength, &argv[count][3]))!=0) return 1;  
		// end section to read key with space

		++count; // advance argc to account for space
		}
		break;
	    }

	    default: {
		break;
	    }
	}
    }	// end for - commandline flag processing

    if (!key_present) {
	fprintf(stderr, "error: no key file\n");
	fprintf(stderr, USAGE);
	return 3;
    }


//You selected

    if (emode) {
	for (i=0; i<blength; ++i) {
	    trans_loc[i] = key_val[i];
	}
    }
    else { 
	// invert permutation
	for (i=0; i<blength; ++i) {
	    trans_loc[key_val[i]] = i;
	}
    }

    return(transpose(blength));
}
