//
// Created by Aimen Fahmi on 2020-04-24.
//

#include <signal.h>
#include "Server.h"

char *handleRequest(char *request, item_t *item) {
    char *return_value = NULL;
    pthread_mutex_lock(&store_access);
    if (strcmp(request, REQUEST_TO_ADD_NEW_ITEM) == 0) {
        return_value = writeItemToStore(item, store);
    } else if (strcmp(request, REQUEST_TO_INCREASE_COUNT_OF_ITEM) == 0) {
        return_value = increaseCountOfItem(item->name, item->amount, store);
    } else if (strcmp(request, REQUEST_TO_BUY_ITEM) == 0) {
        return_value = requestItem(item->name, item->amount, store);
    }
    pthread_mutex_unlock(&store_access);
    return return_value;
}

// Actual execution of the clients request/command
char *treatMessage(msg_t *message) {
    if (isMessage(message) == -1) {
        printf("[-] Message not understood: %s\n", message->content);
        return MSG_IN_WRONG_FORMAT;
    }

    char *command = message->command;
    if (strcmp(command, REQUEST_TO_CLOSE_SERVER) == 0) {return REQUEST_TO_CLOSE_SERVER;}

    char *returned_value = NULL;
    if (message->content != NULL && message->data_type != NULL && strcmp(message->data_type, ITEM_T) == 0) {
        item_t *item = convertStringToItem(message->content);
        returned_value = handleRequest(command, item);
    }

    return returned_value;
}

char *handleConnection(int client_socket) {
    msg_t *msg;
    char *acknowledgment;

    while (1) {
        msg = receiveMsg(client_socket);

        if (strcmp(msg->command, REQUEST_TO_CLOSE_CONNECTION) == 0) {
            return REQUEST_TO_CLOSE_CONNECTION;
        } else if (strcmp(msg->command, REQUEST_TO_CLOSE_SERVER) == 0) {
            return REQUEST_TO_CLOSE_SERVER;
        }

        acknowledgment = treatMessage(msg);
        sendMsg(client_socket, newMsg(ACKNOWLEDGMENT, STRING, acknowledgment));
    }
}

void *threadFunction(void *arg) {
    while (1) {
        int *client_socket;

        pthread_mutex_lock(&connection_queue_access);
        while ((client_socket = dequeue()) == NULL) {
            pthread_cond_wait(&queue_is_empty, &connection_queue_access);
        }
        pthread_mutex_unlock(&connection_queue_access);

        char *return_value = handleConnection(*client_socket);

        if (strcmp(return_value, REQUEST_TO_CLOSE_SERVER) == 0) {
            sqlite3_close_v2(database);
            close(server_socket);
            exit(0);
        } else if (strcmp(return_value, REQUEST_TO_CLOSE_CONNECTION) == 0) {
            close(*client_socket);
        }
    }
}


void sigintHandler(int num) {
    sqlite3_close_v2(database);
    close(server_socket);
    kill(getpid(), SIGKILL);
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
int start() {
    for (int i = 0; i < MAX_THREADS; ++i) {
        pthread_create(&thread_pool[i], NULL, threadFunction, NULL);
    }

    signal(SIGINT, sigintHandler);

    database = openDatabase("../util/sqlite3/Items.db");
    store = createStoreFromDatabase(database);
    server_socket = listenForConnections(PORT, BACKLOG);

    while(1) {
        int *p_client_socket = malloc_safe_mode(sizeof(int));
        *p_client_socket = accept(server_socket, NULL, NULL);

        if (*p_client_socket == -1) {
            printf("[-] Could not accept client\n");
            close(*p_client_socket);
            free(p_client_socket);
            continue;
        }

        pthread_mutex_lock(&connection_queue_access);
        enqueue(p_client_socket);
        pthread_cond_signal(&queue_is_empty);
        pthread_mutex_unlock(&connection_queue_access);
    }
}
#pragma clang diagnostic pop


int main() {
    start();
    return 0;
}