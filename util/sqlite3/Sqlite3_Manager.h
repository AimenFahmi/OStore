//
// Created by Aimen Fahmi on 2020-04-17.
//

#ifndef OSTORE_SQLITE3_MANAGER_H
#define OSTORE_SQLITE3_MANAGER_H

#include <sqlite3.h>
#include "../../data/item/Item.h"
#include "../../data_structures/hashtable/Store_HashTable.h"

void insertItem(sqlite3 *database, item_t *item);
sqlite3 *openDatabase(char *path);
void createItemsTable(sqlite3 *database);
item_t *selectItem(sqlite3 *database, char *name);
int getRowCount(sqlite3 *database);
item_t **selectAllItems(sqlite3 *database);
void insertAllItems(sqlite3 *database, item_t **items, int nb_of_items);
void dumpHashTable(sqlite3 *database, hash_table_t *hashTable);
void displayDatabase(sqlite3 *database);

#endif //OSTORE_SQLITE3_MANAGER_H
