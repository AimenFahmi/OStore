//
// Created by Aimen Fahmi on 2020-04-19.
//

#include "store.h"

item_t **getAllItemsFromStore(store_t *store) {
    return ht_getAllItems(store->stock);
}


store_t *createStoreFromDatabase(sqlite3 *database) {
    store_t *newStore = createStore();
    item_t **items = selectAllItems(database);
    int i = 0;
    while (items[i] != NULL) {
        ht_add(items[i], newStore->stock);
        i++;
    }
    return newStore;
}

// Creates the hashtable that stores the items
store_t *createStore() {
    store_t *newStore = malloc_safe_mode(sizeof(store_t));
    newStore->stock = ht_create(STORE_SIZE);
    return newStore;
}


// Quite lazy way of implementing it, but shouldn't need much more performance
// If there are enough items (the requested amount) the method returns 0 and reduces the count of the data by the "amount"
// Otherwise it returns -1
char *requestItem(char *itemName, int amount, store_t *store) {
    item_t *item = ht_getItem(itemName, store->stock);

    if (item == NULL) {
        return ITEM_NOT_FOUND;
    }

    if (item->amount - amount >= 0) {
        item->amount -= amount;
        ht_add(item, store->stock);
        return SUCCESS;
    } else {
        return ITEM_STOCK_IS_UNSUFFICIENT;
    }
}


// Write the key & value pair to the store
// If the key already exists, it overwrites its value
char *writeItemToStore(item_t *item, store_t *store) {
    ht_add(item, store->stock);
    return SUCCESS;
}

// Increases the count of the data if the latter has a count less than 3
char *increaseCountOfItem(char *itemName, int amount, store_t *store) {
    item_t *item = ht_getItem(itemName, store->stock);

    if (item == NULL) {
        return ITEM_NOT_FOUND;
    } else if(item->amount > 3) {
        return ITEM_STOCK_IS_FULL;
    } else {
        item->amount += amount;
        ht_add(item, store->stock);
        return SUCCESS;
    }
}


// Stores the items of the store into the database
void dumpStoreToDatabase(sqlite3 *database, store_t *store) {
    dumpHashTable(database, store->stock);
}

// Displays the underlying data structure of the store
void displayStore(store_t *store) {
    printTitle("Store");
    ht_print(store->stock);
}
