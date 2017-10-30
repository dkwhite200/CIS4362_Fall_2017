#include <cstdio>
#include <ctype.h>
#include <string.h>

#define USAGE "\n\nUsage : bitdisp [-{bin | acbin}][-{bout | acbout}\n\n"
#define BIT_MASK 0x01

int main(int argc, char *argv[])
{
    bool bin = true;
    bool bout = false;
    bool acbin = false;
    bool acbout = true;
    int c;
    int bits[16];
    int byte = 0;
    int count = 0;

    //Flag bool setting via argument list
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-bin") == 0 || strcmp(argv[i], "-acbout") == 0)
        {
        }
        else if (strcmp(argv[i], "-bout") == 0)
        {
            bin = false;
            bout = true;
        }
        else if (strcmp(argv[i], "-acbin") == 0)
        {
            acbin = true;
            acbout = false;
        }
        else
        {
            fprintf(stderr, "\n\nInvalid Flag Usage\n\n");
            fprintf(stderr, USAGE);
            return 1;
        }
    }

    //This section handles the files based on the flag bool values
    if (bin && bout)
    {
        while ((c = getchar()) != EOF)
        {
            putchar(c);
        }
        return 0;
    }
    else if (acbin && acbout)
    {
        while ((c = getchar()) != EOF)
        {
            if (c == (unsigned char)'0' || c == (unsigned char)'1' || c == (unsigned char)' ')
            {
                putchar(c);
            }
            else
            {
                fprintf(stderr, "\n\nInvalid caracters in ACBIN file\n\n");
                return 2;
            }
        }
        return 0;
    }
    else if (acbin && bout)
    {
        while ((c = getchar()) != EOF)
        {
            if (c == (unsigned char)'0' || c == (unsigned char)' ')
            {}
            else if (c == (unsigned char)'1')
            {
                byte += (BIT_MASK << (7 - count));
            }
            else
            {
                fprintf(stderr, "\n\nInvalid caracters in ACBIN file\n\n");
                return 2;
            }
            count++;
            if (count == 8){
                putchar(byte);
                byte = 0;
                count = 0;
            }
        }
        if (count != 0)
        {
            std::cerr << ;
            fprintf(stderr, "\n\nACBIN file ends in the middle of a byte\n\n");
            return 3;
        }
        return 0;
    }
    else
    {
        while ((c = getchar()) != EOF)
        {
            if (c == (unsigned char)' ')
            {
                continue;
            }
            for (int i = 0; i < 8; i++)
            {
                bits[i] = (c >> (7 - i)) & BIT_MASK;
                if (i == 4)
                {
                    putchar(' ');
                }
                (bits[i] == 0) ? putchar('0') : putchar('1');
            }
            putchar('\n');
        }
        return 0;
    }
}