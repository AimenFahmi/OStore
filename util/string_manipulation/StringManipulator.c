//
// Created by Aimen Fahmi on 2020-04-17.
//

#include "StringManipulator.h"
#include "../common_error_handling/Memory_Error_Handler.h"

char *createString(char *string) {
    if (string == NULL) {
        return "null";
    }
    char *newString = malloc_safe_mode(strlen(string) + 1);
    strcpy(newString, string);
    return newString;
}

// Tokenizes the string according to the delimiter and returns an array containing all the tokens
char **tokenize(char *string, char *delimiters) {
    int number_of_tokens = 0;
    char *temp_string_1 = createString(string);
    char *temp_string_2 = createString(string);

    char *token = strtok(temp_string_1, delimiters);

    while (token != NULL) {
        number_of_tokens++;
        token = strtok(NULL, delimiters);
    }

    char **tokens = malloc_safe_mode((number_of_tokens + 1) * sizeof(char *));

    tokens[0] = strtok(temp_string_2, delimiters);

    for (int i = 1; i < number_of_tokens; ++i) {
        tokens[i] = strtok(NULL, delimiters);
    }

    tokens[number_of_tokens] = NULL;

    return tokens;
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