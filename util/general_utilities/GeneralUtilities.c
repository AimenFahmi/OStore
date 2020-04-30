//
// Created by Aimen Fahmi on 2020-04-19.
//

#include "GeneralUtilities.h"

void printSeparationLine() {
    for (int i = 0; i < 400; ++i) {
        printf("-");
    }
    printf("\n");
}

void printTitle(char *title) {
    printf("\n%s:\n", title);
    for (int i = 0; i < strlen(title)+1; ++i) {
        printf("-");
    }
    printf("\n");
}
