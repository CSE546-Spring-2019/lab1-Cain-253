#include <stdio.h>
#include <string.h>
/**
 * Jeremy Cain
 * Main file for lab 1
 */

/**
 * Handles reading file into buffer.
 *
 * @param  *fpInputFile: File to search.
 * @param  *strSearch: String to search for.
 * @retval Number of times strSearch appears in fpInputFile.
 */
long searchForResults(FILE *fpInputFile, char *strSearch, int size);

/**
 * Starting point for lab.
 *
 * @param  argc: Number of command-line args.
 * @param  argv[]: Command line args as an array of strings.
 * @retval 0
 */
int main(int argc, char *argv[])
{
    //verify there are no missing args
    if (argc != 4)
    {
        printf("Incorrect number of args: %d. Consult readme for usage.", argc);
        return 1;
    }

    //argv[0] is the exe location
    char *strInputFilePath = argv[1];
    char *strSearch = argv[2];
    char *strOutputFilePath = argv[3];

    //open input file
    FILE *fpInputFile = fopen(strInputFilePath, "rb");
    if (fpInputFile == NULL)
    {
        printf("Input file open failed.");
        return 1;
    }

    //get file length
    int iSuccess = fseek(fpInputFile, 0, SEEK_END);
    if (iSuccess != 0)
    {
        printf("File seek failed.");
        return 1;
    }

    long lFileLength = ftell(fpInputFile);
    if (lFileLength < 0)
    {
        printf("File size unknown.");
    }
    fseek(fpInputFile, 0, SEEK_SET);

    //search and count the number of matches, then close the file
    long lCount = searchForResults(fpInputFile, strSearch, strlen(strSearch));
    fclose(fpInputFile);

    //open output file
    FILE *fpOutputFile = fopen(strOutputFilePath, "w");
    if (fpOutputFile == NULL)
    {
        printf("Output file open failed.");
        return 1;
    }

    //print to file and screen. I chose to use text/transation mode instead of binary here.
    fprintf(fpOutputFile, "Size of file is %ld\nNumber of matches = %ld\n", lFileLength, lCount);
    printf("Size of file is %ld\nNumber of matches = %ld\n", lFileLength, lCount);

    return 0;
}

/**
 * This function iterates one character at a time and checks for a match. I was trying
 * to get it to move one Byte at a time, but ran into enough issues to give up. I cannot
 * stress how terrible of a language C is...
 *
 * Also, I don't know why the %!@#& memcpy wasn't working as expected.
 * It worked all the way until the search term was split by a newline, and
 * instead of comparing vs the newline, it pretended it didn't exist. Everything
 * on the Internet kept telling me to open the input file in binary mode, but I
 * ALREADY WAS opening it in binary mode. Anyways, I switched over to a character-by-
 * character comparison, which will fail for binary files but w/e.
 *
 * @param  *fpFile: File pointer to search.
 * @param  *strSearch: String to search for.
 * @param  size: Size of strSearch. As listed at
 *         https://www.geeksforgeeks.org/using-sizof-operator-with-array-paratmeters/,
 *         the sizeof operator can supposedly work differently on a direct array than
 *         on a function parameter. I put this param in as one of many attempts to get
 *         memcmp working as expected, and never took it out when I gave up.
 * @retval The number of matches found.
 */
long searchForResults(FILE *fpFile, char *strSearch, int size)
{
    long lCount = 0;
    int iNumToRevert = (size * -1) + 1; // this is used to seek back to one character shy
                                        // of where fread puts the read head.

    unsigned char buffer[size]; // buffer *should* be larger for performance reasons.

    // loop while there are enough items
    while (fread(buffer, 1, size, fpFile) >= size)
    {
        for (int i = 0; i < size; i++)
        {
            if (buffer[i] != strSearch[i])
            {
                goto skip; // the first time I've used goto in a program. A bad code smell.
            }
        }
        lCount++; // if the for loop finishes without jumping, then all characters must match.

    skip:
        fseek(fpFile, iNumToRevert, SEEK_CUR); // where the go-to goes-to.
    }

    return lCount;
}
