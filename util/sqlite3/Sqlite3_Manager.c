//
// Created by Aimen Fahmi on 2020-04-17.
//

#include "Sqlite3_Manager.h"
#include <sqlite3.h>

sqlite3 *openDatabase(char *path) {
    sqlite3 *database;
    int rv = sqlite3_open(path, &database);

    if (rv != SQLITE_OK) {
        printf("Cannot open database: %s\n", sqlite3_errmsg(database));
        sqlite3_close(database);
        return NULL;
    }

    return database;
}

void createItemsTable(sqlite3 *database) {
    char *error_msg = 0;
    int return_value;

    char *sql = "DROP TABLE IF EXISTS items;"
                //"CREATE TABLE IF NOT EXISTS items(name TEXT PRIMARY KEY, amount INT DEFAULT 0, price REAL DEFAULT 0, description TEXT DEFAULT 'not described', imgUrl TEXT DEFAULT 'no image', category TEXT DEFAULT 'unknown');";
                "CREATE TABLE IF NOT EXISTS items(name TEXT PRIMARY KEY, amount TEXT DEFAULT 'empty', price TEXT DEFAULT 'empty', description TEXT DEFAULT 'not described', imgUrl TEXT DEFAULT 'no image', category TEXT DEFAULT 'unknown');";

    return_value = sqlite3_exec(database, sql, 0, 0, &error_msg);

    if (return_value != SQLITE_OK ) {
        printf("[-] Failed to create table\n");
        printf("[-] SQL error: %s\n", error_msg);
        sqlite3_free(error_msg);
    } else {
        printf("[+] Table 'items' created successfully\n");
    }
}

int getRowCount(sqlite3 *database) {
    sqlite3_stmt *result;
    int return_value;
    int number_of_rows = -1;

    char *sql = "SELECT count(*) FROM items;";
    return_value = sqlite3_prepare_v2(database, sql, -1, &result, 0);

    if (return_value == SQLITE_OK) {
        return_value = sqlite3_step(result);
    } else {
        printf("[-] Failed to count rows in table 'items'\n");
    }

    if (return_value == SQLITE_ROW) {
        number_of_rows = sqlite3_column_int(result, 0);
    } else {
        printf("[-] Failed to count rows in table 'items'\n");
    }

    return number_of_rows;
}

item_t **selectAllItems(sqlite3 *database) {
    int row_count = getRowCount(database);
    item_t **items = malloc_safe_mode((row_count + 1) * sizeof(item_t *));
    sqlite3_stmt *result;

    char *sql = "SELECT * FROM items;";

    int return_value = sqlite3_prepare_v2(database, sql, -1, &result, 0);

    if (return_value != SQLITE_OK) {
        printf("[-] Failed to select all items from table 'items'\n");
        sqlite3_finalize(result);
    }

    for (int i = 0; i < row_count; ++i) {
        return_value = sqlite3_step(result);
        if (return_value == SQLITE_ROW) {
            char *item_name = (char *) sqlite3_column_text(result, 0);
            int amount = sqlite3_column_int(result, 1);
            float price = sqlite3_column_double(result, 2);
            char *description = (char *) sqlite3_column_text(result, 3);
            char *imgUrl = (char *) sqlite3_column_text(result, 4);
            char *category = (char *) sqlite3_column_text(result, 5);
            items[i] = newItem(item_name, amount, price, description, imgUrl, category);
        }
    }

    items[row_count] = NULL;

    sqlite3_finalize(result);

    return items;
}

item_t *selectItem(sqlite3 *database, char *name) {
    sqlite3_stmt *result;
    int return_value;

    char *sql = "SELECT * FROM items WHERE name=@name;";
    return_value = sqlite3_prepare_v2(database, sql, -1, &result, 0);

    if (return_value == SQLITE_OK) {
        int index = sqlite3_bind_parameter_index(result, "@name");
        sqlite3_bind_text(result, index, name, -1, 0);
    } else {
        printf("[-] Failed to select data: %s\n", name);
    }

    int step = sqlite3_step(result);

    item_t *item = NULL;

    if (step == SQLITE_ROW) {
        char *item_name = (char *) sqlite3_column_text(result, 0);
        int amount = sqlite3_column_int(result, 1);
        float price = sqlite3_column_double(result, 2);
        char *description = (char *) sqlite3_column_text(result, 3);
        char *imgUrl = (char *) sqlite3_column_text(result, 4);
        char *category = (char *) sqlite3_column_text(result, 5);
        item = newItem(item_name, amount, price, description, imgUrl, category);
    }

    sqlite3_finalize(result);

    return item;
}

void insertItem(sqlite3 *database, item_t *item) {
    sqlite3_stmt *result;
    int return_value;

    char *sql ="INSERT INTO items VALUES(@name, @amount, @price, @description, @imgUrl, @category);";

    return_value = sqlite3_prepare_v2(database, sql, -1, &result, 0);

    if (return_value == SQLITE_OK) {
        int index = sqlite3_bind_parameter_index(result, "@name");
        sqlite3_bind_text(result, index, item->name, -1, 0);
        index = sqlite3_bind_parameter_index(result, "@amount");
        sqlite3_bind_int(result, index, item->amount);
        index = sqlite3_bind_parameter_index(result, "@price");
        sqlite3_bind_double(result, index, item->price);
        index = sqlite3_bind_parameter_index(result, "@description");
        sqlite3_bind_text(result, index, item->description, -1, 0);
        index = sqlite3_bind_parameter_index(result, "@imgUrl");
        sqlite3_bind_text(result, index, item->imgUrl, -1, 0);
        index = sqlite3_bind_parameter_index(result, "@category");
        sqlite3_bind_text(result, index, item->category, -1, 0);
    } else {
        printf("[-] Failed to execute statement: %s\n", sqlite3_errmsg(database));
        return;
    }

    int step = sqlite3_step(result);

    if (step != SQLITE_DONE) {
        printf("Failed to step: %s\n", sqlite3_errmsg(database));
        return;
    }

    printf("[+] Successfully inserted data '%s'\n", item->name);

    sqlite3_finalize(result);
}

void insertAllItems(sqlite3 *database, item_t **items, int nb_of_items) {
    for (int i = 0; i < nb_of_items; ++i) {
        insertItem(database, items[i]);
    }
}

void dumpHashTable(sqlite3 *database, hash_table_t *hashTable) {
    createItemsTable(database);
    item_t **items = ht_getAllItems(hashTable);
    int number_of_items = 0;
    while (items[number_of_items] != NULL) {
        number_of_items++;
    }
    insertAllItems(database, items, number_of_items);
}

void displayDatabase(sqlite3 *database) {
    printTitle("DataBase:");
    item_t **items = selectAllItems(database);
    for (int i = 0; i < getRowCount(database); ++i) {
        if (items[i] != NULL) {
            printItem(items[i]);
            printf("\n");
        }
    }
}