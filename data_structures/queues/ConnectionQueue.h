//
// Created by Aimen Fahmi on 2020-04-20.
//

#ifndef OSTORE_CONNECTIONQUEUE_H
#define OSTORE_CONNECTIONQUEUE_H

#include "../../util/Common_Libraries.h"

struct node{
    struct node *next;
    int *value;
} node;

typedef struct node node_t;

void enqueue(int *value);
int *dequeue();

#endif //OSTORE_CONNECTIONQUEUE_H
