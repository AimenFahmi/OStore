//
// Created by Aimen Fahmi on 2020-04-24.
//

#include <time.h>
#include "Customer.h"

int customer_buyItem(char *item_name, int amount) {
    item_t *item = newItem(item_name, amount, 0, NULL, NULL, NULL);
    char *item_as_string = convertItemToString(item);
    msg_t *msg = newMsg(REQUEST_TO_BUY_ITEM, ITEM_T, item_as_string);

    sendMsg(customer_socket, msg);
    msg_t *ack_msg = receiveMsg(customer_socket);

    if (strcmp(ack_msg->content, SUCCESS) == 0) {
        printf("[+] Customer was able to buy %d pieces of item '%s'\n", amount, item_name);
    } else if (strcmp(ack_msg->content, ITEM_STOCK_IS_UNSUFFICIENT) == 0) {
        printf("[-] Customer was unable to buy %d pieces of item '%s' because it has been sold out\n", amount, item_name);
        return -1;
    } else if (strcmp(ack_msg->content, ITEM_NOT_FOUND) == 0) {
        printf("[-] Customer was unable to buy %d pieces of item '%s' because the item doesn't exist in the store\n", amount, item_name);
        return -1;
    } else if (strcmp(ack_msg->content, MSG_IN_WRONG_FORMAT) == 0) {
        printf("[-] Message '%s' hasn't been understood by the server\n", msg->content);
        return -1;
    }

    return 1;
}

void automaticTest(int max_transactions, int min_transactions) {
    char *names[] = {"aimen", "alec", "clara"};
    srand(time(NULL));
    for (int i = 0; i < rand()%(max_transactions-min_transactions)+min_transactions; ++i) {
        char *random_name = names[rand()%3];
        int random_amount = rand()%10+1;
        customer_buyItem(random_name, random_amount);
    }
}

int main() {
    msleep(100);
    customer_socket = connectToServer(PORT);
    automaticTest(20, 10);
    closeConnection(customer_socket);
    return 0;
}
