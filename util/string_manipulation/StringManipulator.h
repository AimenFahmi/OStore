//
// Created by Aimen Fahmi on 2020-04-17.
//

#ifndef OSTORE_STRINGMANIPULATOR_H
#define OSTORE_STRINGMANIPULATOR_H

char *createString(char *string);
char *concat(char *str1, char *str2);
char* substr(const char *src, int start_index, int end_index);
char **getTokens(char *string, char *delimiter);

#endif //OSTORE_STRINGMANIPULATOR_H
