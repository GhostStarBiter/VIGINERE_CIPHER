//
// Created by mrgreen on 03.08.17.
//
#include <string.h>
#include "operate.h"

#define ASCII_Z 90
#define ASCII_A 65
#define A_TO_Z  26

#define KEYWORD_MAX_LEN 12

char* check(char* keyword, char* string, int* status){
    int keyword_len = (int)strlen(keyword);
    if(keyword_len > KEYWORD_MAX_LEN){
        *status = 1;
        return string= " Keyword too long! Exit.";
    }

    for(int i = 0; i < keyword_len; i++){
        if((keyword[i] <= 65) && (keyword[i] >= 90)){
            *status = 1;
            return string = "ERROR! Keyword must consist of capital letters!\n";
        }
    }
    return string = "Processing...\n";
};

void encode(char* keyword, char* origin_word, FILE* coded_file){
    int keyword_len = (int)strlen(keyword);
    int coded = 0;
    int j = 0;
    for(int i = 0; i < strlen(origin_word); i++){
        /**loop keyword if original word is longer**/
        if(i >= keyword_len){
            if((j = i/keyword_len) < 1)
                j = 1;
            coded = (keyword[i - j*keyword_len] + origin_word[i] + keyword_len - 1);
        }
        else
        {
            coded = (keyword[i] + origin_word[i] + keyword_len - 1);
        }

        /**adjust coded letter**/
        if(coded > ASCII_Z)
            if((coded -= ASCII_Z) > ASCII_Z)
                coded -= A_TO_Z ;
        if(coded < ASCII_A)
            coded += A_TO_Z;
        fputc((char)coded, coded_file);
    }
}

void decode(char* keyword, char* coded_word, FILE* decoded_file){
    int keyword_len = (int)strlen(keyword);
    int decoded = 0;
    int j = 0;

    for(int i = 0; i < strlen(coded_word); i++){
        if(i >= keyword_len){
            if((j = i/keyword_len) < 1)
                j = 1;
            decoded = coded_word[i] - keyword[i - j*keyword_len] + A_TO_Z;
        }
        else
        {
            decoded = coded_word[i] - keyword[i] + A_TO_Z;
        }

        decoded += ASCII_A - keyword_len;

        if(decoded > ASCII_Z)
            decoded -= A_TO_Z;
        if(decoded < ASCII_A)
            decoded += A_TO_Z;

        fputc((char)decoded, decoded_file);
    }
}
