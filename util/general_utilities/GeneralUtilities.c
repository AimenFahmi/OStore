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

int msleep(long msec) {
    struct timespec ts;
    int res;

    if (msec < 0)
    {
        errno = EINVAL;
        return -1;
    }

    ts.tv_sec = msec / 1000;
    ts.tv_nsec = (msec % 1000) * 1000000;

    do {
        res = nanosleep(&ts, &ts);
    } while (res && errno == EINTR);

    return res;
}
