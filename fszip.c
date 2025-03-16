#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h> // Include for int32_t

#define MYLIMIT 16384

int main(int argc, char** argv) {

    //if no files are specified, the program will exit with return code 1
    if (1 == argc) {
        printf("fszip: file1 [file2 ...]\n");
        return 1;
    }

    //loop through all files specifed on command line
    for (int i = 1; i < argc; i++) {
        char line[MYLIMIT];
        FILE* fp = fopen(argv[i], "r");
        //check if file opened successfully
        if (fp == NULL) {
            perror("Error opening file");
        }

        //iterate line by through input file and compress the content.
        while (fgets(line, MYLIMIT, fp) != NULL) {
            int rLen = 1; //holds the length of each character
            char curr = line[0]; //holds the character while we are counting its run length
            char prev = '\0'; //holds previous value
            int len = strlen(line); //length of line we are currently on

            //iterates through each character in the current line
            for (int j = 1; j < len; j++) {
                prev = curr; //update previous to hold the current character
                curr = line[j]; //set curr to the next character in the line

                //checks if we have consecutive equal characters
                if (curr == prev) {
                    rLen++; //if we do have consecutive equal characters, then increment run length
                } else {
                    //if we do not have consecutive equal characters
                    fwrite(&rLen, sizeof(int32_t), 1, stdout); //write out a 4-byte integer (the run length) in binary format
                    fwrite(&prev, sizeof(char), 1, stdout); //the single character in ASCII
                    rLen = 1; //reset run length
                }
            }

            //make sure the line is not empty
            if(len > 0){
                //write the last run of characters on a line
                fwrite(&rLen, sizeof(int32_t), 1, stdout); //write out a 4-byte integer (the run length) in binary format
                fwrite(&curr, sizeof(char), 1, stdout); //the single character in ASCII

            }

        }//end while

        fwrite("\n", sizeof(char), 1, stdout);  //write newline character at end of each line
        fclose(fp); //close file

    }//end for

    return 0;

}