//
// Created by Aimen Fahmi on 2020-04-24.
//

#ifndef OSTORE_SERVER_H
#define OSTORE_SERVER_H

#include "../data/store/store.h"
#include "../communication_protocol/ConnectionHandler.h"
#include "../communication_protocol/CommunicationProtocol.h"
#include "../data_structures/queues/ConnectionQueue.h"
#include "../data_structures/hashtable/RequestManaging_HashTable.h"
#include <pthread.h>

#define MAX_THREADS 100
#define BACKLOG 100
#define CONNECTION_HANDLED "CH"

/** Data **/
#define REQUEST_MANAGER_SIZE 100

store_t *store;
sqlite3 *database;
int server_socket;

pthread_t thread_pool[MAX_THREADS];
rm_hash_table_t *requestManager;

pthread_mutex_t request_manager_access = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t connection_queue_access = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t queue_is_empty = PTHREAD_COND_INITIALIZER;

pthread_mutex_t tokenize_protector = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t printing_access = PTHREAD_MUTEX_INITIALIZER;


/** Functions **/
int run();
void *threadFunction(void *arg);
char *handleConnection(int client_socket);
char *treatMessage(msg_t *message);

#endif //OSTORE_SERVER_H


