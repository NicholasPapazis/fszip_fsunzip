#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h> // Include for int32_t

#define MYLIMIT 16384

int main(int argc, char** argv) {

    if (1 == argc) {
        printf("fszip: file1 [file2 ...]\n");
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        char line[MYLIMIT];
        FILE* fp = fopen(argv[i], "r");
        if (fp == NULL) {
            perror("Error opening file");
        }

        while (fgets(line, MYLIMIT, fp) != NULL) {
            int rLen = 1;
            char curr = line[0];
            char prev = '\0';
            int len = strlen(line);

            for (int j = 1; j < len; j++) {
                prev = curr;
                curr = line[j];

                if (curr == prev) {
                    rLen++;
                } else {
                    fwrite(&rLen, sizeof(int32_t), 1, stdout);
                    fwrite(&prev, sizeof(char), 1, stdout);
                    rLen = 1;
                }
            }
            if(len > 0){
                fwrite(&rLen, sizeof(int32_t), 1, stdout);
                fwrite(&curr, sizeof(char), 1, stdout);

            }

        }
        fwrite("\n", sizeof(char), 1, stdout);
        fclose(fp);
    }

    return 0;
}