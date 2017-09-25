#include <stdio.h>
#include <ctype.h>

#define DEBUG 0
#define USAGE "Usage: nybble_sub [-{e|d}] [-{h|b}] -k<keyfile>\n"
#define LAST_NEWLINE 0
#define MAXVALS 16
char hexchar[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c','d', 'e', 'f'};

int key_val[MAXVALS];
int sub_val[MAXVALS];

int get_bin_key(FILE*);
int get_key_file(int, char*);
int encrypt();

int encrypt() {
    int un, ln;
    int c;

    while ((c = getchar()) != EOF) 
    {
	// unpack nybbles
	un = c >> 4;
	ln = c & 0xf;

	// substitute nybbles
	un = sub_val[un];
	ln = sub_val[ln];

	// repack nybbles
	c = (un << 4) + ln;

	putchar(c);
    }
    return 0;
}

int get_key_file(int in_hex, char *keyfilename) {
	FILE *fd;
	char c;

	if (DEBUG) fprintf(stderr, "In get_key_file, mode = %d, file = %s\n", in_hex, keyfilename);
	fd = fopen(keyfilename,"r");
	if (fd == NULL) return -1;

	if (in_hex) {
	    while ((c = fgetc(fd)) != EOF) {
		fputc(c, stderr);
	    }
	    fprintf(stderr, "Hex key not supported yet\n");
	}
	else {
	    return(get_bin_key(fd));
	}
	return 0;
}
    
int get_bin_key(FILE *keyfiled) {
    int un, ln;
    int c;
    int i=0;

    while ((c = fgetc(keyfiled)) != EOF) {
	un = c >> 4;
	ln = c & 0xf;
	key_val[i] = un;
	key_val[++i] = ln;

	if (DEBUG) {
		putchar(hexchar[un]);
		putchar(hexchar[ln]);
	}
	if (++i >= MAXVALS) break;
    }
    if (i < MAXVALS) {
	fprintf(stderr,"Too few values in key file: %d\n",i);
	return -2;
    }
    return 0;
}


int main(int argc, char **argv)
{
    int hex_key = 0;
    int emode = 1;
    int count;
    int i;

//    for (d=0; d<16; ++d) putchar(hexchar[d]);
//    putchar('\n');

    if (argc < 2) {
	fprintf(stderr, "error: too few args\n");
	fprintf(stderr, USAGE);
	return 1;
    }
    for (count = 1; count < argc; ++count) {
	if (argv[count][0] != '-') {
	    fprintf(stderr, "error: too few args\n");
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
	    case 'h': {
		hex_key = 1;
		break;
	    }
	    case 'b': {
		hex_key = 0;
		break;
	    }
	    case 'k': {
		if (DEBUG) fprintf(stderr, "Getting key from %s\n", &argv[count][2]);
	        get_key_file(hex_key,&argv[count][2]);
		break;
	    }
	    default: {
		break;
	    }
	}
    }


    if (emode) {
	for (i=0; i<MAXVALS; ++i) {
	    sub_val[i] = key_val[i];
	}
    }
    else { 
	// invert permutation
	for (i=0; i<MAXVALS; ++i) {
	    sub_val[key_val[i]] = i;
	}
    } 
    return(encrypt());
}
