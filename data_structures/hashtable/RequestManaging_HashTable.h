//
// Created by Aimen Fahmi on 2020-05-01.
//

#ifndef OSTORE_REQUESTMANAGING_HASHTABLE_H
#define OSTORE_REQUESTMANAGING_HASHTABLE_H

#include "../../util/Common_Libraries.h"
#include "../../util/common_error_handling/Memory_Error_Handler.h"
#include <pthread.h>

#define IS_NOT_BEING_USED -1
#define IS_BEING_USED 0

/** data **/
typedef struct {
    int is_being_used;
    char *command;
    int amount_used;
    pthread_cond_t condition_var;
} rm_ht_status_t;

typedef struct rm_ht_entry_t{
    char *name;
    rm_ht_status_t *status;
    struct rm_ht_entry_t *next;
} rm_ht_entry_t;

typedef struct {
    int size;
    int used_size;
    rm_ht_entry_t **entries;
} rm_hash_table_t;

/** functions **/
rm_hash_table_t *rm_ht_createHashTable(int size);
rm_ht_entry_t *rm_ht_createEntry(char *item_name, rm_ht_status_t *item_status);
int rm_ht_hash(char *key, rm_hash_table_t *hashTable);
void rm_ht_add(rm_ht_entry_t *entry, rm_hash_table_t *hashTable);
void rm_ht_remove(char *key, rm_hash_table_t *hashTable);
rm_ht_status_t *rm_ht_createStatus(int is_being_used, char *command_used_on_item, int amount_used);
rm_ht_status_t *rm_ht_getStatus(char *item_name, rm_hash_table_t *hashTable);
void rm_ht_setStatus(char *item_name, int status, rm_hash_table_t *hashTable);
void rm_ht_printStatus(rm_ht_status_t *status);
rm_ht_entry_t **rm_ht_getAllEntries(rm_hash_table_t *hashTable);
rm_ht_entry_t **rm_ht_getAllItems(rm_hash_table_t *hashTable);
void rm_ht_printEverything(rm_hash_table_t *hashTable);
void rm_ht_print(rm_hash_table_t *hashTable);
int isBeingUsed(char *item_name, rm_hash_table_t *hashTable);
int rm_ht_contains(char *item_name, rm_hash_table_t *hashTable);

#endif //OSTORE_REQUESTMANAGING_HASHTABLE_H
