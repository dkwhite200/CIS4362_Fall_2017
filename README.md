# CIS4362_Fall_2017_Ex-1

Exercise - 3: Experiment with S-P networks

Task 1: Write a program bfreq that reads from stdin and writes to stdout, and counts the number of each byte value present in the input. For each of the 256 byte values (0 through 255, or 0x00 through 0xff), it outputs the number of each value seen in the input to stdout. 

By default, it writes one value per line with the value in ASCII-coded hex, then a space, then the actual frequency count of that value.

With the -n flag, the value and space are omitted.

With the -c flag, the space is replaced with a comma.

With the -L<N> flag, where N is an integer between 1 and 256, N values (or value pairs) are printed per line, with two hex characters per byte value and a constant number of characters per frequency or percent value (again, leading spaces), with a semicolon ';' and space after each entry (either a frequency or byte value-frequency pair).

Example1: if byte 00 has frequency 105, 01 has frequency 3, and 02 has frequency 17, then with -L1 flag the first three lines of output would be

00 105;
01   3;
02  17;
assuming that no character has frequency greater than 999. (The line with 3 has two extra spaces in it before the 3, the line with 17 has one extra space before the 17.)

Example2: Same as example 1 except the flags are -L3 and -c. The first output line would be

00,105; 01,  3; 02, 17;

Example 3: byte 00 has frequency 105, 01 has frequency 123,456,789, 02 has frequency 17, 03 has frequency 3,456, then with -n -L1 flags the first four lines of output would be 
      105;
123456789;
       17;
     3456; 
assuming that no character has frequency greater than 999,999,999.

With the -p flag, the percent (normalized frequency) is given with resolution to one decimal point instead of the frequency count (e.g., if there are 50 characters in the input, and 10 of them are 'e', then the line for value hex 65 will have 10 by default, or 20.0 if the -p flag is present).

With the -s flag, the output is sorted from most frequent character to least frequent character.

Task 2:

Use your nybble substitution and byte transposition programs individually to encrypt at least three English text files, at least three source code files in the same language, and at least three executable files (or other file that is not text) and determine the frequency histograms for each, and the average frequency histograms. Comment on the degree of variation.

Now run substitution followed by transposition and transposition followed by substitution and obtain histograms. Comment.

Submit source code and a report with your results (note that not all histograms need be submitted - only some representatives or average histograms) and a discussion.
