//
// Created by Aimen Fahmi on 2020-04-24.
//

#ifndef OSTORE_CONNECTIONHANDLER_H
#define OSTORE_CONNECTIONHANDLER_H

#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include "../util/Common_Libraries.h"
#include "CommunicationProtocol.h"

#define SIZE_RECEIVED "SR"

int connectToServer(char *port);
int listenForConnections(char *port, int backlog);
void sendMsg(int socket, msg_t *msg);
msg_t *receiveMsg(int socket);
void closeConnection(int socket);
void closeServer(int socket);

#endif //OSTORE_CONNECTIONHANDLER_H
