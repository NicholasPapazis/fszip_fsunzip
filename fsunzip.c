#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char** argv) {

    //if no files are specified, the program will exit with return code 1
    if (1 == argc) {
        printf("fsunzip: file1 [file2 ...]\n");
        return 1; //exit with status code 1
    }

    //loop through all files specifed on command line
    for (int i = 1; i < argc; i++) {

        FILE* fp = fopen(argv[i], "rb"); //open zip file

        //if fp is NULL, then there was an issue opening the file
        if (fp == NULL) {
            exit(1); //exit with status code 1
        }


        int32_t rLen; //holds 4-byte run length of character
        char curr; //holds character that will be decompressed

        //loop through compressed zip file entries
        while (fread(&rLen, sizeof(int32_t), 1, fp) == 1) {
            //checks if reading character failed
            if (fread(&curr, sizeof(char), 1, fp) != 1) {
                fprintf(stderr, "could not read character\n");
                fclose(fp);
                return 1;
            }

            //loop the run length
            for (int i = 0; i < rLen; i++) {
                printf("%c", curr); //print current character to stdout
            }

            //if we read character successfully, and it is a new line character
            if (fread(&curr, sizeof(char), 1, fp) == 1 && curr == '\n') {
                printf("%c", curr); //print the new line character to stdout
            } else {
                ungetc(curr, fp); //pushes c back to stream, if next char is not a new line character
            }
        }

        fclose(fp); //close file

    }
    return 0;
}