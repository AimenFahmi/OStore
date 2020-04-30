//
// Created by Aimen Fahmi on 2020-04-25.
//

#include <time.h>
#include <sys/time.h>
#include "Shop.h"

int shop_writeItem(item_t *item) {
    msg_t *msg = newMsg(REQUEST_TO_ADD_NEW_ITEM, ITEM_T, convertItemToString(item));

    sendMsg(shop_socket, msg);
    msg_t *ack_msg = receiveMsg(shop_socket);

    if (strcmp(ack_msg->content, MESSAGE_NOT_UNDERSTOOD) == 0) {
        printf("[-] Message '%s' hasn't been understood by the server\n", msg->content);
        return -1;
    } else if (strcmp(ack_msg->content, SUCCESS) == 0) {
        printf("[+] Shop was able to write item '%s' with count %d\n", item->name, item->amount);
    }

    return 1;
}

int shop_increaseCountOfItem(char *item_name, int amount) {
    item_t *item = newItem(item_name, amount, 0, NULL, NULL, NULL);
    msg_t *msg = newMsg(REQUEST_TO_INCREASE_COUNT_OF_ITEM, ITEM_T, convertItemToString(item));

    sendMsg(shop_socket, msg);
    msg_t *ack_msg = receiveMsg(shop_socket);

    if (strcmp(ack_msg->content, SUCCESS) == 0) {
        printf("[+] Shop was able to add %d pieces of item '%s'\n", amount, item_name);
    } else if (strcmp(ack_msg->content, ITEM_STOCK_IS_FULL) == 0) {
        printf("[-] Shop was unable to increase count of item '%s' by %d because its stock is full\n", item_name, amount);
    } else if (strcmp(ack_msg->content, ITEM_NOT_FOUND) == 0) {
        printf("[-] Shop was unable to increase count of item '%s' by %d because the item doesn't exist in the store\n", item_name, amount);
    }

    if (strcmp(ack_msg->content, MESSAGE_NOT_UNDERSTOOD) == 0) {
        printf("[-] Message '%s' hasn't been understood by the server\n", msg->content);
        return -1;
    }

    return 1;
}

void automaticTest(int max_transactions, int min_transactions) {
    char *names[] = {"aimen", "alec", "clara"};
    char *method_names[] = {"shop_writeItem", "shop_increaseCountOfItem"};
    srand(time(NULL));
    for (int i = 0; i < rand()%(max_transactions-min_transactions)+min_transactions; ++i) {
        char *random_method = method_names[rand()%2];
        char *random_name = names[rand()%3];
        int random_amount = rand()%10+1;

        if (strcmp(random_method, method_names[0]) == 0) {
            int random_price = rand()%3000 + 3000;
            shop_writeItem(newItem(random_name, random_amount, random_price, NULL, NULL, NULL));
        } else if (strcmp(random_method, method_names[1]) == 0) {
            shop_increaseCountOfItem(random_name, random_amount);
        }
    }
}

int main() {
    shop_socket = connectToServer(PORT);
    automaticTest(100, 80);
    closeConnection(shop_socket);
    return 0;
}