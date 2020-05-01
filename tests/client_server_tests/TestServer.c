//
// Created by Aimen Fahmi on 2020-04-30.
//

#include "../../communication_protocol/ConnectionHandler.h"

int main() {
    int server_socket = listenForConnections("5555", 100);

    int socket = accept(server_socket, NULL, NULL);
    
    while (1) {
        msg_t *msg = receiveMsg(socket);
        if (msg == NULL) {
            break;
        }
        printMsg(msg);
    }

    close(socket);
    close(server_socket);
    return 0;
}

