#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "operate.h"

#define STRINGS_EQUAL 0
#define PATH_LEN 256
#define WORD_MAX_LEN 25

char path[PATH_LEN];
int input;
char word_from_file[WORD_MAX_LEN] = {0};
int char_pos = 0;


int main(int argc, char* argv[]){

    if(argc < 3){
        printf("You must specify text file in same directory and operation type!\n");
        printf("Example: [program_name] [file_name] [operation: code/decode]\n");
        exit(EXIT_FAILURE);
    }

    getcwd(path, PATH_LEN);
    strcat(path, "/");
    strcat(path, argv[1]);

    FILE* input_file;
    if((input_file = fopen(path, "r")) == NULL){
        printf("Error while opening specified file: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    printf("OK. Specified file opened. ");

                            /***************
                            *** CODING ***
                            ****************/
    if(strcmp(argv[2], "code") == STRINGS_EQUAL){
        char* response = NULL;
        int check_status = 0;
        printf("%s\n", check(response, &check_status));
        if(check_status)
            exit(EXIT_FAILURE);

        FILE* encrypted;
        if((encrypted = fopen("coded", "w+")) == NULL){
            printf("Error while creating new file: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }

        /** READ INPUT FILE BY CHARACTERS **/
        while(!feof(input_file)){   //read characters from file while end of file is reached
            input = fgetc(input_file);
            /** check is the read character a letter **/
            if(input >=65 && input <=90 ||
               input >= 97 && input <= 122){
                /**adjust all lowercase letters to uppercase**/
                if(input >= 97 && input <= 122)
                    input -= 32;
                word_from_file[char_pos] = (char) input;
                char_pos++;
            }
            else
            {
                encode(word_from_file, encrypted);
                fputc(input, encrypted);
                char_pos = 0;
                memset(word_from_file, 0, WORD_MAX_LEN);
            }
        }
        fputc(EOF, encrypted);
        printf("Encrypted file created.\n");
        fclose(encrypted);
    }
    else
                            /***************
                            *** DECODING ***
                            ****************/
    if(strcmp(argv[2], "decode") == STRINGS_EQUAL){
        char* response = NULL;
        int check_status = 0;
        printf("%s\n", check(response, &check_status));
        if(check_status)
            exit(EXIT_FAILURE);

        FILE* decrypted;
        if((decrypted = fopen("decoded", "w+")) == NULL){
            printf("Error while creating new file: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }

        /** READ INPUT FILE BY CHARACTERS **/
        while(!feof(input_file)){
            input = fgetc(input_file);
            /** check is the read character a letter **/
            if(input >=65 && input <=90 ||
               input >= 97 && input <= 122){
                /**adjust all lowercase letters to uppercase**/
                if(input >= 97 && input <= 122)
                    input -= 32;
                word_from_file[char_pos] = (char) input;
                char_pos++;
            }
            else
            {
                decode(word_from_file, decrypted);
                fputc(input, decrypted);
                char_pos = 0;
                memset(word_from_file, 0, WORD_MAX_LEN);
            }
        }
        fputc(EOF, decrypted);
        printf("Decrypted file created.\n");
        fclose(decrypted);
    }
    else
    {
        printf("Invalid operation type: %s\n", argv[2]);
        printf("Available operations on file: code, decode\n");
        exit(EXIT_FAILURE);
    }
    fclose(input_file);
    return 0;
}
