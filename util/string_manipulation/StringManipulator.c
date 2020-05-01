//
// Created by Aimen Fahmi on 2020-04-17.
//

#include "StringManipulator.h"
#include "../common_error_handling/Memory_Error_Handler.h"

char *createString(char *string) {
    if (string == NULL) {
        return NULL;
    }
    char *newString = malloc_safe_mode(strlen(string) + 1);
    strcpy(newString, string);
    return newString;
}

char *concat(char *str1, char *str2) {
    if (str1 == NULL) {
        str1 = "";
    } else if (str2 == NULL) {
        str2 = "";
    }
    char string[strlen(str1) + strlen(str2)];
    memset(string, 0, strlen(string));
    strcat(string, str1);
    strcat(string, str2);
    return createString(string);
}

char* substr(const char *src, int start_index, int end_index) {
    // get length of the destination string
    int len = end_index - start_index;

    // allocate (len + 1) chars for destination (+1 for extra null character)
    char *dest = (char*)malloc(sizeof(char) * (len + 1));

    // extracts characters between start_index'th and end_index'th index from source string
    // and copy them into the destination string
    for (int i = start_index; i < end_index && (*(src + i) != '\0'); i++)
    {
        *dest = *(src + i);
        dest++;
    }

    // null-terminate the destination string
    *dest = '\0';

    // return the destination string
    return dest - len;
}

char **getTokens(char *string, char *delimiter) {
    char delim = delimiter[0];
    int nb_of_tokens = 0;

    for (int i = 0; i < strlen(string); ++i) {
        if (string[i] == delim) {nb_of_tokens++;}
    }

    char **tokens = malloc_safe_mode(((++nb_of_tokens)+1) * sizeof(char *));

    int end_of_previous_token = 0;
    for (int j = 0; j < nb_of_tokens; ++j) {
        for (int i = end_of_previous_token; i < strlen(string); ++i) {
            if (j == nb_of_tokens-1 && i == strlen(string) - 1) {
                tokens[j] = substr(string, end_of_previous_token, i+1);
            }
            if (string[i] == delim) {
                tokens[j] = substr(string, end_of_previous_token, i);
                end_of_previous_token = i+1;
                break;
            }
        }
    }

    tokens[nb_of_tokens] = NULL;

    return tokens;
}