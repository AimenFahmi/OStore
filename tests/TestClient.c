//
// Created by Aimen Fahmi on 2020-04-30.
//

#include "../communication_protocol/ConnectionHandler.h"

int main() {
    int client_socket = connectToServer("5555");

    item_t *item = newItem("aimen", 542, 0, NULL, NULL, NULL);
    char *item_as_string = convertItemToString(item);
    msg_t *msg = newMsg(REQUEST_TO_BUY_ITEM, ITEM_T, item_as_string);

    for (int i = 0; i < 50; ++i) {
        sendMsg(client_socket, msg);
    }

    close(client_socket);
    return 0;
}

