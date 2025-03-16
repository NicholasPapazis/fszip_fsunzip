#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char** argv) {

    //if no files are specified, the program will exit with return code 1
    if (1 == argc) {
        printf("fsunzip: file1 [file2 ...]\n");
        return 1; //exit with status code 1
    }

    for (int i = 1; i < argc; i++) {
        FILE* inputFile = fopen(argv[i], "rb");
        if (inputFile == NULL) {
            perror("could not open file");
            return 1;
        }

        int32_t rLen;
        char curr;

        while (fread(&rLen, sizeof(int32_t), 1, inputFile) == 1) {
            if (fread(&curr, sizeof(char), 1, inputFile) != 1) {
                fprintf(stderr, "could not read character\n");
                fclose(inputFile);
                return 1;
            }

            for (int i = 0; i < rLen; i++) {
                printf("%c", curr); //print to stdout
            }

            //check for new line character
            if (fread(&curr, sizeof(char), 1, inputFile) == 1 && curr == '\n') {
                printf("%c", curr); //print new line
            } else {
                ungetc(curr, inputFile);
            }
        }

        fclose(inputFile);

    }
    return 0;
}