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

    if(argc < 5){
        printf("USAGE: \n\t ./vgnr [operation: code/decode] [path/to/file/with/original(or crypted)/text] [path/to/create/file/with/encrypted(or decrypted)/text] [encode/decode keyword]\n");
        exit(EXIT_FAILURE);
    }

    FILE* input_file;
    if((input_file = fopen(argv[2], "r")) == NULL){
        printf("Error while opening specified file: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    printf("OK. Specified file opened. ");

    if(argv[4] == NULL){
        printf("You must specify keyword! (no longer than 12 characters)\n");
        exit(EXIT_FAILURE);
    }

                            /***************
                            *** CODING ***
                            ****************/
    if(strcmp(argv[1], "code") == STRINGS_EQUAL){
        char* response = NULL;
        int check_status = 0;
        printf("%s\n", check(argv[4], response, &check_status));
        if(check_status)
            exit(EXIT_FAILURE);

        FILE* encrypted;
        if((encrypted = fopen(argv[3], "w+")) == NULL){
            printf("Error while creating new file: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }

        /** READ INPUT FILE BY CHARACTERS **/
        while(!feof(input_file)){   //read characters from file while end of file is reached
            input = fgetc(input_file);
            /** check is the read character a letter **/
            if((input >=65 && input <=90) ||
                    (input >= 97 && input <= 122)){
                /**adjust all lowercase letters to uppercase**/
                if((input >= 97) && (input <= 122))
                    input -= 32;
                word_from_file[char_pos] = (char) input;
                char_pos++;
            }
            else
            {
                encode(argv[4], word_from_file, encrypted);
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
    if(strcmp(argv[1], "decode") == STRINGS_EQUAL){
        char* response = NULL;
        int check_status = 0;
        printf("%s\n", check(response, &check_status));
        if(check_status)
            exit(EXIT_FAILURE);

        FILE* decrypted;
        if((decrypted = fopen(argv[3], "w+")) == NULL){
            printf("Error while creating new file: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }

        /** READ INPUT FILE BY CHARACTERS **/
        while(!feof(input_file)){
            input = fgetc(input_file);
            /** check is the read character a letter **/
            if((input >=65 && input <=90) ||
                    (input >= 97 && input <= 122)){
                /**adjust all lowercase letters to uppercase**/
                if((input >= 97) && (input <= 122))
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
        printf("Invalid operation type: %s\n", argv[1]);
        printf("Available operations on file: code, decode\n");
        exit(EXIT_FAILURE);
    }
    fclose(input_file);
    return 0;
}
