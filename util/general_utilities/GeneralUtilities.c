//
// Created by Aimen Fahmi on 2020-04-19.
//

#include "GeneralUtilities.h"
#include "../../data/store/store.h"

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

void startTimer() {
    start = clock();
}

double getTime(char *functionName) {
    stop = clock();
    double cpu_time = ((double) (stop - start)) / CLOCKS_PER_SEC;
    printf("\n[+] Time taken by %s(): %0.3f\n\n", functionName, cpu_time);
    return cpu_time;
}
