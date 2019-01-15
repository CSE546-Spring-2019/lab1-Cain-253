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
long searchForResults(FILE *fpInputFile, char *strSearch);

/**
 * Starting point for lab.
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

    long lCount = searchForResults(fpInputFile, strSearch);

    fclose(fpInputFile);

    FILE *fpOutputFile = fopen(strOutputFilePath, "w");
    if (fpOutputFile == NULL)
    {
        printf("Output file open failed.");
        return 1;
    }

    fprintf(fpOutputFile, "Size: %ld\nMatches: %ld\n", lFileLength, lCount);
    printf("Size: %ld\nMatches: %ld\n", lFileLength, lCount);

    return 0;
}

long searchForResults(FILE *fpFile, char *strSearch)
{
    long lCount = 0;
    int iSize = sizeof(strSearch);
    unsigned char buffer[iSize];

    while (fread(buffer, 1, iSize, fpFile) >= iSize)
    {
        printf("buffer: \n%s\n", buffer);
        if (memcmp(strSearch, buffer, iSize) == 0)
        {
            lCount++;
        }
        fseek(fpFile, ((iSize - 1) * -1), SEEK_CUR);
    }

    return lCount;
}
