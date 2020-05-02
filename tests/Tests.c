//
// Created by Aimen Fahmi on 2020-04-30.
//

#include "Tests.h"
#include "../data_structures/hashtable/RequestManaging_HashTable.h"

int communicationProtocolTest() {
    item_t *item = newItem("aimen", 43, 542.65323, "very good", "https://what", "category");

    msg_t *message1 = newMsg(REQUEST_TO_ADD_NEW_ITEM, ITEM_T, convertItemToString(item));
    msg_t *message2 = newMsg("Some defined command", FLOAT, "435.6546");
    msg_t *message3 = newMsg(REQUEST_TO_CLOSE_SERVER, NULL, NULL);

    char * msg_to_send1 = convertMessageToString(message1);
    char * msg_to_send2 = convertMessageToString(message2);
    char * msg_to_send3 = convertMessageToString(message3);

    msg_t *received_msg1 = convertStringToMessage(msg_to_send1);
    msg_t *received_msg2 = convertStringToMessage(msg_to_send2);
    msg_t *received_msg3 = convertStringToMessage(msg_to_send3);

    if (message1->length == received_msg1->length && strcmp(message1->command, received_msg1->command) == 0 &&
    strcmp(message1->content, received_msg1->content) == 0 && strcmp(message1->data_type, received_msg1->data_type) == 0) {
        printf("[+] msg_sent == msg_received (1): Success\n");
    } else {
        printf("[-] msg_sent == msg_received (1): Failure\n");
    }

    if (message2->length == received_msg2->length && strcmp(message2->command, received_msg2->command) == 0 &&
        strcmp(message2->content, received_msg2->content) == 0 && strcmp(message2->data_type, received_msg2->data_type) == 0) {
        printf("[+] msg_sent == msg_received (2): Success\n");
    } else {
        printf("[-] msg_sent == msg_received (2): Failure\n");
    }

    if (message3->length == received_msg3->length && strcmp(message3->command, received_msg3->command) == 0 &&
        message3->content == NULL && message3->data_type == NULL) {
        printf("[+] msg_sent == msg_received (3): Success\n");
    } else {
        printf("[-] msg_sent == msg_received (3): Failure\n");
    }

    return 0;
}

int tokenizationTest() {
    item_t *item = newItem("aimen", 542, 0, NULL, NULL, NULL);
    char *item_as_string = convertItemToString(item);
    char **tokens = getTokens(item_as_string, MESSAGE_DELIMITER);

    int i = 0;
    while (tokens[i] != NULL) {
        printf("%s\n", tokens[i]);
        i++;
    }
    return 0;
}

int requestManagementTest() {
    char *randomNames[] = {"rafik", "aimen", "clara", "alec", "yassin", "abdullah", "fatima", "said", "rajab", "alem", "dafali", "soufian",
                           "azzouz", "khadija", "yassmine", "houssam", "moustapha", "ismail", "burgers", "tea", "meat", "chicken", "coca cola"};
    char *randomCommands[] = {REQUEST_TO_BUY_ITEM, REQUEST_TO_INCREASE_COUNT_OF_ITEM, REQUEST_TO_ADD_NEW_ITEM};
    int randomUsage[] = {IS_BEING_USED, IS_NOT_BEING_USED};

    int nb_names = 22;
    int nb_commands = 3;
    int nb_uses = 2;
    //srand(time(NULL));

    rm_hash_table_t * hashTable = rm_ht_createHashTable(5);

    for (int i = 0; i < 100; ++i) {
        int randomAmount = rand()%100;
        int name_index = rand()%nb_names;
        int command_index = rand()%nb_commands;
        int usage_index = rand()%nb_uses;

        rm_ht_status_t *status = rm_ht_createStatus(randomUsage[usage_index], randomCommands[command_index], randomAmount);

        rm_ht_entry_t *entry = rm_ht_createEntry(randomNames[name_index], status);
        rm_ht_add(entry, hashTable);
    }
    rm_ht_remove("yassmine", hashTable);
    
    rm_ht_print(hashTable);
    printf("\n\n");
    rm_ht_printEverything(hashTable);

    return 0;
}

int main() {
    requestManagementTest();
    return 0;
}
