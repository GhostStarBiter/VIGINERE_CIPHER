//
// Created by mrgreen on 03.08.17.
//
#include <string.h>
#include "operate.h"

#define ASCII_Z 90
#define ASCII_A 65
#define A_TO_Z  26


/** ALPHABET OFFSET **/
#define OFFSET 11  //value must be from 0 to 25

/** KEYWORD **/
static char keyword[] = "ALPHA";


#define KEYWORD_MAX_LEN 12
#define KEYWORD_LEN (int)strlen(keyword)

char* check(char* string, int* status){

    if(KEYWORD_LEN > KEYWORD_MAX_LEN){
        *status = 1;
        return string= " Keyword too long! Exit.";
    }

    for(int i = 0; i < KEYWORD_LEN; i++){
        if((keyword[i] <= 65) && (keyword[i] >= 90)){
            *status = 1;
            return string = "ERROR! Word must consist of capital letters!\n";
        }
    }
    return string = "Processing...\n";
};

void encode(char* origin_word, FILE* coded_file){
    int coded = 0;
    int j = 0;
    for(int i = 0; i < strlen(origin_word); i++){
        /**loop keyword if original word is longer**/
        if(i >= KEYWORD_LEN){
            if((j = i/KEYWORD_LEN) < 1)
                j = 1;
            coded = (keyword[i - j*KEYWORD_LEN] + origin_word[i] + OFFSET - 1);
        }
        else
        {
            coded = (keyword[i] + origin_word[i] + OFFSET - 1);
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

void decode(char* coded_word, FILE* decoded_file){
    int decoded = 0;
    int j = 0;

    for(int i = 0; i < strlen(coded_word); i++){
        if(i >= KEYWORD_LEN){
            if((j = i/KEYWORD_LEN) < 1)
                j = 1;
            decoded = coded_word[i] - keyword[i - j*KEYWORD_LEN] + A_TO_Z;
        }
        else
        {
            decoded = coded_word[i] - keyword[i] + A_TO_Z;
        }

        decoded += ASCII_A - OFFSET;

        if(decoded > ASCII_Z)
            decoded -= A_TO_Z;
        if(decoded < ASCII_A)
            decoded += A_TO_Z;

        fputc((char)decoded, decoded_file);
    }
}