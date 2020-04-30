//
// Created by Aimen Fahmi on 2020-04-17.
//

#include "Item.h"

item_t *newItem(char *name, int amount, float price, char *description, char *imgUrl, char *category) {
    item_t *item = malloc_safe_mode(sizeof(item_t));

    item->name = createString(name);
    item->description = createString(description);
    item->imgUrl = createString(imgUrl);
    item->category = createString(category);

    item->amount = amount;
    item->price = price;

    return item;
}

void destroyItem(item_t *item) {
    free(item->name);
    free(item->category);
    free(item->imgUrl);
    free(item->description);
    free(item);
}

void printItem(item_t *item) {
    printf("[name: %s, amount: %d, price: %f, description: %s, imgUrl: %s, category: %s]", item->name, item->amount,
            item->price, item->description, item->imgUrl, item->category);
}
