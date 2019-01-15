#include <stdio.h>
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
long searchForResults(FILE *fpInputFile, char *strSearch);

/**
 * Starting point for lab. In a better program, it would delegate execution to other methods.
 *
 * @param  argc: Number of command-line args.
 * @param  argv[]: Command line args as an array of strings.
 * @retval 0
 */
int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Incorrect number of args: %d. Consult readme for usage.\nPress Enter to exit.", argc);
        return 1;
    }

    //argv[0] is the exe location
    char *strInputFilePath = argv[1];
    char *strSearch = argv[2];
    char *strOutputFilePath = argv[3];

    printf("input file path: %s\n", strInputFilePath);
    FILE *fpInputFile = fopen(strInputFilePath, "rb");
    if (fpInputFile == NULL)
    {
        printf("Input file open failed.");
        return 1;
    }

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

    printf("search string: %s\n", strSearch);
    long lCount = searchForResults(fpInputFile, strSearch);

    fclose(fpInputFile);

    printf("output file path: %s\n", strOutputFilePath);
    FILE *fpOutputFile = fopen(strOutputFilePath, "w");
    if (fpOutputFile == NULL)
    {
        printf("Output file open failed.");
        return 1;
    }

    fprintf(fpOutputFile, "Size: %ld\nMatches: %ld", lFileLength, lCount);
    printf("Size: %ld\nMatches: %ld", lFileLength, lCount);

    printf("Complete.");
    return 0;
}

long searchForResults(FILE *fpFile, char *strSearch)
{
    //TODO: implement
    return 525600;
}
