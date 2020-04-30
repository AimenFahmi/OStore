//
// Created by Aimen Fahmi on 2020-04-17.
//

#ifndef OSTORE_HASHTABLE_H
#define OSTORE_HASHTABLE_H

#define VALUE_AFTER_REMOVAL 0

#include "../../util/Common_Libraries.h"
#include "../../util/common_error_handling/Memory_Error_Handler.h"
#include "../../data/item/Item.h"

/** data **/

typedef struct ht_item{
    char *key;
    item_t *value;
    struct ht_item *next;
} ht_item;

typedef struct {
    int size;
    ht_item **entries;
} hash_table_t;

/** functions **/

hash_table_t *ht_create(int size);
ht_item *create_ht_item(char *key, item_t *value);
int hash(char *key, hash_table_t *hashTable);
void ht_add(item_t *item, hash_table_t *hashTable);
item_t *ht_getItem(char *key, hash_table_t *hashTable);
void ht_removeItem(char *key, hash_table_t *hashTable);
ht_item **ht_getAll_ht_Items(hash_table_t *hashTable);
item_t **ht_getAllItems(hash_table_t *hashTable);
void ht_printEverything(hash_table_t *hashTable);
void ht_print(hash_table_t *hashTable);

#endif //OSTORE_HASHTABLE_H
