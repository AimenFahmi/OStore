//
// Created by Aimen Fahmi on 2020-05-01.
//

#include "RequestManaging_HashTable.h"

// Memory allocation for a hashtable
rm_hash_table_t *rm_ht_createHashTable(int size) {

    rm_hash_table_t *newHashTable = malloc_safe_mode(sizeof(rm_hash_table_t));
    newHashTable->entries = malloc_safe_mode(size * sizeof(rm_ht_item *));

    for (int i = 0; i < size; ++i) {
        newHashTable->entries[i] = NULL;
    }

    newHashTable->size = size;

    return newHashTable;
}


// Memory allocation for the given KeyValuePair
rm_ht_item *rm_ht_createEntry(char *item_name, rm_ht_item_status_t *item_status) {

    rm_ht_item *item = malloc_safe_mode(sizeof(rm_ht_item));

    item->name = item_name;
    item->status = item_status;
    item->next = NULL;

    return item;
}


// Returns a hash code
int rm_ht_hash(char *item_name, rm_hash_table_t *hashTable) {
    unsigned int value = 0;
    int key_length = strlen(item_name);

    for (int i = 0; i < key_length; ++i) {
        value = value * 37 + item_name[i];
    }

    value = value % hashTable->size;
    return value;
}


// If the data wasn't in the hashtable already, it adds it
// else it overwrites it's value
void rm_ht_add(char *item_name, rm_ht_item_status_t *item_status, rm_hash_table_t *hashTable) {

    char *key = item_name;
    int index = rm_ht_hash(key, hashTable);
    rm_ht_item *entry = hashTable->entries[index];

    if (entry == NULL) {
        hashTable->entries[index] = rm_ht_createEntry(key, item_status);
        return;
    }

    rm_ht_item *prev;

    while (entry != NULL) {
        if (strcmp(entry->name, key) == 0) {
            memcpy(entry->status, item_status, sizeof(rm_ht_item));
            return;
        }
        prev = entry;
        entry = prev->next;

    }

    prev->next = rm_ht_createEntry(key, item_status);
}


// Searches for the key in the hashtable
// If found, it returns it's corresponding value
// else, it returns null
rm_ht_item_status_t *rm_ht_getStatus(char *item_name, rm_hash_table_t *hashTable) {
    int index = rm_ht_hash(item_name, hashTable);
    rm_ht_item *entry = hashTable->entries[index];

    if (entry == NULL) {
        return NULL;
    }

    if (strcmp(item_name, entry->name) == 0) {
        if (hashTable->entries[index]->status->is_being_used == IS_BEING_USED) {return hashTable->entries[index]->status;}
    }

    while (entry != NULL) {

        if (strcmp(item_name, entry->name) == 0) {
            if (hashTable->entries[index]->status->is_being_used == IS_BEING_USED) {return entry->status;}
        }

        entry = entry->next;
    }

    return NULL;
}


// Lazy delete by setting the nb_items of the Item to NULL
void rm_ht_remove(char *key, rm_hash_table_t *hashTable) {
    rm_ht_item_status_t *item_status = rm_ht_getStatus(key, hashTable);
    if (item_status != NULL) {
        item_status->is_being_used = IS_NOT_BEING_USED;
    }
}

void rm_ht_printStatus(rm_ht_item_status_t *status) {
    printf("[%d, %s, %d]", status->is_being_used, status->command, status->amount_used);
}

// Prints the hashtable on the console
void rm_ht_print(rm_hash_table_t *hashTable) {
    if (hashTable == NULL) {
        printf("Can't print a null hash table");
        exit(-1);
    }

    for (int i = 0; i < hashTable->size; ++i) {

        rm_ht_item *entry = hashTable->entries[i];
        if (entry != NULL) {
            printf("at index %d:\t\t", i);

            while (entry != NULL) {
                if (entry->status->is_being_used == IS_BEING_USED) {
                    printf("%s -> ", entry->name);
                    rm_ht_printStatus(entry->status);
                    printf("\t\t");
                } else {
                    printf("%s -> not_being_used", entry->name);
                }
                entry = entry->next;
            }

            printf("\n");

        }

    }

    printf("\n");
}

// Prints every data in the hashtable even if removed
void rm_ht_printEverything(rm_hash_table_t *hashTable) {
    rm_ht_item **items = rm_ht_getAllEntries(hashTable);
    int i = 0;
    while(items[i] != NULL) {
        printf("Key: %s\t\tValue: ", items[i]->name);
        rm_ht_printStatus(items[i]->status);
        printf("\n");
        i++;
    }
}


// Returns all the items available in the hashtable (in a hashtable compatible format)
rm_ht_item **rm_ht_getAllEntries(rm_hash_table_t *hashTable) {
    rm_ht_item **entries = malloc_safe_mode(hashTable->size * sizeof(rm_ht_item *));

    int j = 0;
    for (int i = 0; i < hashTable->size; ++i) {
        rm_ht_item *entry = hashTable->entries[i];
        if (entry != NULL) {
            while (entry != NULL) {
                rm_ht_item *actualEntry = rm_ht_createEntry(entry->name, entry->status);
                entries[j++] = actualEntry;
                entry = entry->next;
            }
        }
    }

    return entries;
}


// Returns all the items available in the hashtable
rm_ht_item **rm_ht_getAllItems(rm_hash_table_t *hashTable) {
    int j = 0;

    // j becomes the number of items in the hashtable
    for (int i = 0; i < hashTable->size; ++i) {
        rm_ht_item *entry = hashTable->entries[i];
        if (entry != NULL) {
            while (entry != NULL) {
                j++;
                entry = entry->next;
            }
        }
    }

    rm_ht_item **items = malloc_safe_mode((j + 1) * sizeof(rm_ht_item *));

    j = 0;
    for (int i = 0; i < hashTable->size; ++i) {
        rm_ht_item *entry = hashTable->entries[i];
        if (entry != NULL) {
            while (entry != NULL) {
                rm_ht_item_status_t *status= entry->status;

                char *name = entry->name;
                int is_being_used = status->is_being_used;
                char *command_used_on_item = status->command;
                int amount_used = status->amount_used;

                rm_ht_item *item = rm_ht_createEntry(name, rm_ht_createStatus(is_being_used, command_used_on_item, amount_used));
                items[j++] = item;
                entry = entry->next;
            }
        }
    }

    items[j] = NULL;

    return items;
}

rm_ht_item_status_t *rm_ht_createStatus(int is_being_used, char *command_used_on_item, int amount_used) {
    rm_ht_item_status_t *status = malloc_safe_mode(sizeof(rm_ht_item_status_t));

    status->is_being_used = is_being_used;
    status->command = command_used_on_item;
    status->amount_used = amount_used;

    return status;
}
