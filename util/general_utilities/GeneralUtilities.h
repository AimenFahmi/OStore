//
// Created by Aimen Fahmi on 2020-04-19.
//

#ifndef OSTORE_GENERALUTILITIES_H
#define OSTORE_GENERALUTILITIES_H

#include "../Common_Libraries.h"
#include <errno.h>
#include <time.h>

void printTitle(char *title);
int msleep(long msec);

clock_t start, stop;
void startTimer();
double getTime(char *functionName);

#endif //OSTORE_GENERALUTILITIES_H
