#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define DEBUG 0
#define true 1
#define false 0
#define BYTE_MASK 0xFF
#define NYBBLE_MASK 0xFF
#define LAST_NEWLINE 0
#define MAXBYTES 16
//bin to HEX
// if nothing is listed, this is bin to Hex
char hexchar[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c','d', 'e', 'f'};

int main(int argc, char **argv)
{
    int c;
    int un, ln;
    int count=0;

	// This part is courtesy of Spinner
   // By default assume bin and xout are true
     //   int bin = true;
        int bout = false;
        int xin = false;
     //   int xout = true;

    for (int i = 1; i < argc; i++) { // First thing in this array is the program name, so start at the first flag.
        // Only need to check for bout and xin since bin and xout are the defaults
        if(strcmp(argv[i], "-bout") == 0) {
                bout = true;
         //       xout = false;
        } else if(strcmp(argv[i], "-xin") == 0) {
                xin = true;
         //       bin = false;
        }
    }

   if (bout==false && xin==false) {

    	while ((c = getchar()) != EOF)
    	{
        un = c >> 4;
        ln = c & 0xf;
        putchar(hexchar[un]);
        putchar(hexchar[ln]);
        if (++count >= MAXBYTES) {
            putchar('\n');
            count = 0;
        }
        else putchar(' ');
    }
    if (LAST_NEWLINE) putchar('\n');
    return 0;
}

else {

//Else if you have -xin -bout
//Hex to bin 
    int c,d;
   // unsigned char un, ln;
    int state = 0;

    while ((c = getchar()) != EOF)
    {
        if (DEBUG) fputc(c, stderr);
        if (isdigit(c)) {
                if (DEBUG) fprintf(stderr, " is digit\n");
                d = c - '0';
                if (DEBUG) fprintf(stderr, "c-'0' is %d\n",d);
                if (DEBUG) fprintf(stderr, "State is %d\n",state);
                if (state==0) {
                        un = d<<4;
                        state = 1;
                        if (DEBUG) fputc(un, stderr);
                        }
                else {
                        ln = d;
                        if (DEBUG) fputc(ln, stderr);
                        d = un + ln;
                        // d = d & BYTE_MASK;
                        putchar(d);
                        state = 0;
                }
        }
        else if (isalpha(c)) {
                if (DEBUG) fprintf(stderr, " is alpha\n");
                d = toupper(c);
                if (DEBUG) fputc(d, stderr);
                if (DEBUG) fprintf(stderr, " is upper\n");
                d = d - 'A';
                d = d + 10;
                if (DEBUG) fprintf(stderr, "d-'A' is %d\n",d);
                if (d >= 16) {
                        fprintf(stderr, "Bad character: %c\n", (char) c);
                        return 1;
                }
                /* otherwise, character between A and F */
                if (state==0) {
                        un = d<<4;
                        state = 1;
                }
                else {
                        ln = d;
                        d = un + ln;
                        // d = d & BYTE_MASK;
                        putchar(d);
                        state = 0;
                }
        }
        else if (isspace(c))
        { /* whitespace - ignore */
                if (DEBUG) fprintf(stderr, " is whitespace\n");
        }
        else {
                fprintf(stderr, "Bad character: %c\n", (char) c);
                return 2;
        }
    }
    return 0;
}

} // End of main
