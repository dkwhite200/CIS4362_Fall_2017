#include <cstdio>
#include <ctype.h>

#define DEBUG 0
#define MAXBYTES 256
#define BIT_MASK 0x01
#define USAGE "\n\nUsage : bitrans [-{e | d}][-b<blocksize>] - k<keyfile>\n\n"

int get_key_file(int, char *);
int get_key(int, FILE *);
int key_test(int);
int transpose(int);
int get_block(int, int *);
int transpose_block(int, int *);
int output_block(int, int *);

int key_map[256];
int trans_loc[256];
int block_count = 0;

int main(int argc, char *argv[])
{
    bool e = false;
    bool d = false;
    bool key_present = false;
    int len = 8;
    int error_code = 0;

    if (argc < 3)
    {
        fprintf(stderr, "\n\nbitrans call has too few arguments\n\n");
        fprintf(stderr, USAGE);
        return 1;
    }
    if (argc > 4)
    {
        fprintf(stderr, "\n\nbitrans call has too many arguments\n\n");
        fprintf(stderr, USAGE);
        return 1;
    }
    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] == '-')
        {
            fprintf(stderr, "error: bad flag: %s\n", &argv[i][0]);
            fprintf(stderr, USAGE);
            return 7;
        }

        switch (argv[i][1])
        {
        case 'e':
            e = true;
            break;

        case 'd':
            d = true;
            break;

        case 'b':
            if (DEBUG)
                fprintf(stderr, "Block length %s\n", &argv[i][2]);
            sscanf(&argv[i][2], "%d", &len);
            break;

        case 'k':
            if (argv[i][2] != '\0')
            {
                key_present = true;
                if (DEBUG)
                    fprintf(stderr, "Getting key from %s\n", &argv[i][2]);
                error_code = get_key_file(len, &argv[i][2]);
                if (error_code != 0)
                {
                    return error_code;
                }
            }
            else
            {
                key_present = true;
                if (DEBUG)
                    fprintf(stderr, "Getting key from %s\n", &argv[i][3]);
                error_code = get_key_file(len, &argv[i][3]);
                if (error_code != 0)
                {
                    return error_code;
                }
                i++;
            }
            break;

        default:
            fprintf(stderr, "Invalid flag \"%s\" used", &argv[i][3]);
            fprintf(stderr, USAGE);
            return 7;
        }
    }

    //throw error if no key is present
    if (!key_present)
    {
        fprintf(stderr, "Error: no key file\n");
        fprintf(stderr, USAGE);
        return 8;
    }

    //throw error if -d and -e are used
    if (e & d)
    {
        fprintf(stderr, "Error: cannot use both \"-d\" and \"-e\"\n");
        fprintf(stderr, USAGE);
        return 7;
    }

    //Run encrypt or decrypt
    else if (e)
    {
        for (int i = 0; i < len * 8; i++)
        {
            trans_loc[i] = key_map[i];
        }
    }
    else if (d)
    {
        for (int i = 0; i < len * 8; i++)
        {
            trans_loc[key_map[i]] = i;
        }
    }
    else
    {
        fprintf(stderr, "Error: must have either \"-e\" or \"-d\"\n");
        fprintf(stderr, USAGE);
        return 7;
    }

    return (transpose(len));
}

//This function gets the FILE object to pass to the get_key function; returns any error code
int get_key_file(int len, char *file_name)
{
    FILE *fd;
    if (DEBUG)
        fprintf(stderr, "In get_key_file, length of key must be blocksize, len = %d, file = %s\n", len, file_name);
    fd = fopen(file_name, "r");
    if (fd == NULL)
    {
        fprintf(stderr, "Unable to open key_file = %s\n", file_name);
        return 2;
    }
    return (get_key(len, fd));
}

//This function gets the key_map for encryption/decryption and tests it in key_test
int get_key(int len, FILE *fd)
{
    int key_len = len * 8 - 1;
    int c;
    int count = 0;

    while ((c = fgetc(fd)) != EOF)
    {
        key_map[count] = c;
        if (DEBUG)
            fprintf(stderr, "Key[%d] = %d\n", count, c);
        if (count++ > (key_len))
        {
            fprintf(stderr, "key contains too many bytes; key must be 8 * <n> bytes in length\n");
            return 3;
        }
    }
    if (count < (key_len))
    {
        fprintf(stderr, "key contains too few bytes; key must be 8 * <n> bytes in length\n");
        return 4;
    }
    return key_test(len);
}

//This function tests the key for any errorous values
int key_test(int len)
{
    int i = 0;
    int marked[len * 8];
    for (i = 0; i < len * 8; ++i)
    {
        marked[i] = 0;
    }
    if (DEBUG)
        fprintf(stderr, "In check_key, len = %d\n", len);
    for (i = 0; i < len; ++i)
    {
        if (DEBUG)
            fprintf(stderr, "\t%d:\t%d\n", i, key_map[i]);
        if (key_map[i] >= len * 8)
        {
            fprintf(stderr, "Key value too large at %d: %d\n", i, key_map[i]);
            return 5;
        }
        if (marked[key_map[i]])
        {
            fprintf(stderr, "Duplicate key value at %d: %d\n", i, key_map[i]);
            return 6;
        }
        marked[key_map[i]] = 1;
    }
    return 0;
}

//This function calls the other function dependencies; argument is the length of block given by -b<n>
int transpose(int blen)
{
    int newblock[blen * 8];
    int rv = 0;

    if (DEBUG)
        fprintf(stderr, "Starting transpose\n");

    while ((rv = get_block(blen, newblock)) == 0)
    {
        if (DEBUG)
            fprintf(stderr, "Block=");
        if (DEBUG)
            output_block(blen, newblock);
        if (DEBUG)
            fprintf(stderr, "\n");

        rv = transpose_block(blen, newblock);
        if (!rv)
            output_block(blen, newblock);
    }
    return rv;
}

int get_block(int blen, int *block)
{
    int c = 0;
    int count = 0;
    int i = 0;
    if (DEBUG)
        fprintf(stderr, "Getting block %d\n", block_count);
    while ((c = getchar()) != EOF)
    {
        for (i = count * 8; i < (8 * (count + 1)); i++)
        {
            block[i] = (c >> (7 - i)) & BIT_MASK;
            if (DEBUG)
                putchar(block[i]);
        }
        count++;
        if (count == blen)
            break;
    }
    if (c == EOF)
    {
        if (count)
        {
            fprintf(stderr, "\nIncomplete block, length=%d\n", i);
            return (count);
        }
        return (1);
    }
    else
        return (count % blen);
}

int transpose_block(int blen, int *block)
{
    int bit = 0;
    int tmp[blen * 8];

    if (DEBUG)
        fprintf(stderr, "Transposing block %d\n", block_count++);
    for (bit = 0; bit < blen * 8; ++bit)
    {
        tmp[bit] = block[bit];
    }
    if (DEBUG)
        fprintf(stderr, "tmp=");
    if (DEBUG)
        output_block(blen, tmp);
    if (DEBUG)
        fprintf(stderr, "\n");
    for (bit = 0; bit < blen * 8; ++bit)
    {
        block[bit] = 0;
    }
    for (bit = 0; bit < blen * 8; ++bit)
    {
        block[trans_loc[bit]] = tmp[bit];
    }
    return 0;
}

int output_block(int blen, int *block)
{
    for (int i = 0; i < blen * 8; ++i)
    {
        putchar(block[i]);
    }
    return 0;
}