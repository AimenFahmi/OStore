//
// Created by Aimen Fahmi on 2020-04-19.
//

#ifndef OSTORE_STORE_H
#define OSTORE_STORE_H

#include "../../util/Common_Libraries.h"
#include "../../data_structures/hashtable/HashTable.h"
#include "../../util/sqlite3/Sqlite3_Manager.h"
#include "../../communication_protocol/CommunicationProtocol.h"

#define STORE_SIZE 100

typedef struct {
    hash_table_t *stock;
} store_t;

store_t *createStore();
store_t *createStoreFromDatabase(sqlite3 *database);
void displayStore(store_t *store);
char * requestItem(char *itemName, int amount, store_t *store);
char * increaseCountOfItem(char *itemName, int amount, store_t *store);
char * writeItemToStore(item_t *item, store_t *store);
item_t **getAllItemsFromStore(store_t *store);
void dumpStoreToDatabase(sqlite3 *database, store_t *store);


#endif //OSTORE_STORE_H
