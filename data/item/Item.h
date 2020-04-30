//
// Created by Aimen Fahmi on 2020-04-17.
//

#ifndef OSTORE_ITEM_H
#define OSTORE_ITEM_H

#include <math.h>
#include "../../util/Common_Libraries.h"
#include "../../util/common_error_handling/Memory_Error_Handler.h"
#include "../../util/string_manipulation/StringManipulator.h"

typedef struct {
    char *name;
    int amount;
    float price;
    char *description;
    char *imgUrl;
    char *category;
} item_t;

item_t *newItem(char *name, int amount, float price, char *description, char *imgUrl, char *category);
void destroyItem(item_t *item);
void printItem(item_t *item);

#endif //OSTORE_ITEM_H
