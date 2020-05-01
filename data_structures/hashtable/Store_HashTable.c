//
// Created by Aimen Fahmi on 2020-04-17.
//

#include "Store_HashTable.h"


// Memory allocation for a hashtable
hash_table_t *ht_create(int size) {

    hash_table_t *newHashTable = malloc_safe_mode(sizeof(hash_table_t));
    newHashTable->entries = malloc_safe_mode(size * sizeof(ht_item *));

    for (int i = 0; i < size; ++i) {
        newHashTable->entries[i] = NULL;
    }

    newHashTable->size = size;

    return newHashTable;
}


// Memory allocation for the given KeyValuePair
ht_item *create_ht_item(char *key, item_t *value) {

    ht_item *newEntry = malloc_safe_mode(sizeof(ht_item));

    newEntry->value = value;
    newEntry->key = key;
    newEntry->next = NULL;

    return newEntry;
}


// Returns a hash code
int hash(char *key, hash_table_t *hashTable) {
    unsigned int value = 0;
    int key_length = strlen(key);

    for (int i = 0; i < key_length; ++i) {
        value = value * 37 + key[i];
    }

    value = value % hashTable->size;
    return value;
}


// If the data wasn't in the hashtable already, it adds it
// else if overwrites it's value
void ht_add(item_t *item, hash_table_t *hashTable) {

    char *key = item->name;
    int index = hash(key, hashTable);
    ht_item *entry = hashTable->entries[index];

    if (entry == NULL) {
        hashTable->entries[index] = create_ht_item(key, item);
        return;
    }

    ht_item *prev;

    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) {
            memcpy(entry->value, item, sizeof(item_t));
            return;
        }
        prev = entry;
        entry = prev->next;

    }

    prev->next = create_ht_item(key, item);
}


// Searches for the key in the hashtable
// If found, it returns it's corresponding value
// else, it returns null
item_t *ht_getItem(char *key, hash_table_t *hashTable) {
    int index = hash(key, hashTable);
    ht_item *entry = hashTable->entries[index];

    if (entry == NULL) {
        return NULL;
    }

    if (strcmp(key, entry->key) == 0) {
        if (hashTable->entries[index]->value->amount != VALUE_AFTER_REMOVAL)
            return hashTable->entries[index]->value;
    }

    while (entry != NULL) {

        if (strcmp(key, entry->key) == 0) {
            if (hashTable->entries[index]->value->amount != VALUE_AFTER_REMOVAL)
                return entry->value;
        }

        entry = entry->next;
    }

    return NULL;
}


// Lazy delete by setting the nb_items of the Item to NULL
void ht_removeItem(char *key, hash_table_t *hashTable) {
    item_t *value = ht_getItem(key, hashTable);
    ht_add(
            newItem(value->name, VALUE_AFTER_REMOVAL, value->price, value->description, value->imgUrl, value->category),
            hashTable);
}


// Prints the hashtable on the standard output
void ht_print(hash_table_t *hashTable) {
    if (hashTable == NULL) {
        printf("Can't print a null hash table");
        exit(-1);
    }

    for (int i = 0; i < hashTable->size; ++i) {

        ht_item *entry = hashTable->entries[i];
        if (entry != NULL) {
            printf("at index %d:\t\t", i);

            while (entry != NULL) {
                if (entry->value->amount != VALUE_AFTER_REMOVAL) {
                    printf("%s -> ", entry->key);
                    printItem(entry->value);
                    printf("\t\t");
                } else {
                    printf("%s -> removed", entry->key);
                }
                entry = entry->next;
            }

            printf("\n");

        }

    }

    printf("\n");
}

// Prints every data in the hashtable even if removed
void ht_printEverything(hash_table_t *hashTable) {
    ht_item **keyValuePairs = ht_getAll_ht_Items(hashTable);
    int i = 0;
    while(keyValuePairs[i] != NULL) {
        printf("Key: %s\t\tValue: ", keyValuePairs[i]->key);
        printItem(keyValuePairs[i]->value);
        printf("\n");
        i++;
    }
}


// Returns all the items available in the hashtable (in a hashtable compatible format)
ht_item **ht_getAll_ht_Items(hash_table_t *hashTable) {
    ht_item **keyValuePairs = malloc_safe_mode(hashTable->size * sizeof(ht_item *));

    int j = 0;
    for (int i = 0; i < hashTable->size; ++i) {
        ht_item *entry = hashTable->entries[i];
        if (entry != NULL) {
            while (entry != NULL) {
                ht_item *actualEntry = create_ht_item(entry->key, entry->value);
                keyValuePairs[j++] = actualEntry;
                entry = entry->next;
            }
        }
    }

    return keyValuePairs;
}


// Returns all the items available in the hashtable
item_t **ht_getAllItems(hash_table_t *hashTable) {
    int j = 0;

    // j becomes the number of items in the hashtable
    for (int i = 0; i < hashTable->size; ++i) {
        ht_item *entry = hashTable->entries[i];
        if (entry != NULL) {
            while (entry != NULL) {
                j++;
                entry = entry->next;
            }
        }
    }

    item_t **items = malloc_safe_mode((j + 1) * sizeof(item_t *));

    j = 0;
    for (int i = 0; i < hashTable->size; ++i) {
        ht_item *entry = hashTable->entries[i];
        if (entry != NULL) {
            while (entry != NULL) {

                char *name = entry->value->name;
                int amount = entry->value->amount;
                float price = entry->value->price;
                char *description = entry->value->description;
                char *imgUrl = entry->value->imgUrl;
                char *category = entry->value->category;

                item_t *item = newItem(name, amount, price, description, imgUrl, category);
                items[j++] = item;
                entry = entry->next;
            }
        }
    }

    items[j] = NULL;

    return items;
}
