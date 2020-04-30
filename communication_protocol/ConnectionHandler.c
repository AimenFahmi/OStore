//
// Created by Aimen Fahmi on 2020-04-24.
//

#include "ConnectionHandler.h"
#include "CommunicationProtocol.h"

/*int connectToServer(char *port) {
    struct addrinfo hints, *server_info, *p;
    int return_value;
    int socket_to_return = -1;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    return_value = getaddrinfo(NULL, port, &hints, &server_info);

    if (return_value != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(return_value));
        exit(-1);
    }

    for (p = server_info; p != NULL ; p = p->ai_next) {
        socket_to_return = socket(p->ai_family, p->ai_socktype, p->ai_protocol);

        if (socket_to_return == -1) {
            printf("[-] Failed to create socket\n");
            continue;
        }

        return_value = connect(socket_to_return, p->ai_addr, p->ai_addrlen);

        if (return_value == -1) {
            close(socket_to_return);
            printf("[-] Failed to connect to server on port %s\n", port);
            close(socket_to_return);
            continue;
        }

        break;
    }

    if (p == NULL) {
        printf("[-] Failed to connect to server on port %s and has to exit\n", port);
        close(socket_to_return);
        exit(-1);
    }

    freeaddrinfo(server_info);

    return socket_to_return;
}


int listenForConnections(char *port, int backlog) {
    int socket_to_return = -1;
    struct addrinfo hints, *server_info, *p;
    int yes = 1;
    int return_value;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE; // use my IP

    if ((return_value = getaddrinfo(NULL, port, &hints, &server_info)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(return_value));
        exit(-1);
    }

    // loop through all the results and bind to the first we can
    for(p = server_info; p != NULL; p = p->ai_next) {
        if ((socket_to_return = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
            perror("server: socket");
            continue;
        }

        if (setsockopt(socket_to_return, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
            perror("setsockopt");
            exit(1);
        }

        if (bind(socket_to_return, p->ai_addr, p->ai_addrlen) == -1) {
            close(socket_to_return);
            perror("server: bind");
            continue;
        }

        break;
    }

    freeaddrinfo(server_info); // all done with this structure

    if (p == NULL) {
        fprintf(stderr, "server: failed to bind\n");
        exit(1);
    }

    if (listen(socket_to_return, backlog) == -1) {
        perror("listen");
        exit(1);
    }

    return socket_to_return;
}*/

int connectToServer(char *port) {
    struct sockaddr_in server_address = {0};
    int newSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (newSocket < 0) {
        printf("[-] Socket creation failed\n");
        exit(-1);
    }

    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(atoi(port));

    int rv = connect(newSocket, (struct sockaddr *) &server_address, sizeof(server_address));

    if (rv < 0) {
        printf("[-] Connection to server on port %s failed\n", port);
        close(newSocket);
        exit(-1);
    }

    return newSocket;
}

int listenForConnections(char *port, int backlog) {
    int iSetOption = 1;
    struct sockaddr_in server_address = {0};

    int newSocket = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(newSocket, SOL_SOCKET, SO_REUSEADDR, (char*)&iSetOption,
               sizeof(iSetOption));

    if (newSocket == -1) {
        printf("[-] Socket creation failed\n");
        exit(-1);
    }

    server_address.sin_port = htons(atoi(port));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;

    int binding_status = bind(newSocket, (struct sockaddr *) &server_address, sizeof(server_address));

    if (binding_status < 0) {
        printf("[-] Binding to client port %s failed\n", port);
    }

    listen(newSocket, backlog);

    return newSocket;
}

msg_t *receiveMsgUsingSize(int socket) {
    char buff[21];
    int rv = recv(socket, buff, sizeof(buff), 0);

    if (rv < 0) {
        printf("[-] Couldn't receive message\n");
        close(socket);
        exit(-1);
    }

    int msg_size = atoi(buff);

    char message[msg_size];
    rv = recv(socket, message, sizeof(message), 0);

    if (rv < 0) {
        printf("[-] Couldn't receive message\n");
        close(socket);
        exit(-1);
    }

    return convertStringToMessage(createString(message));
}

void sendMsgUsingSize(int socket, msg_t *msg) {
    char *message = convertMessageToString(msg);
    char msg_size[21];
    sprintf(msg_size, "%ld", (strlen(message) + 1));
    int rv = send(socket, msg_size, sizeof(msg_size), 0);

    if (rv < 0) {
        printf("[-] Couldn't send msg_size: %s\n", msg_size);
        close(socket);
        exit(-1);
    }

    rv = send(socket, message, strlen(message) + 1, 0);

    if (rv < 0) {
        printf("[-] Couldn't send message: %s\n", msg->content);
        close(socket);
        exit(-1);
    }
}

void closeConnectionUsingSize(int socket) {
    msg_t *msg = newMsg(REQUEST_TO_CLOSE_SERVER, NULL, NULL);
    sendMsgUsingSize(socket, msg);
}

void sendMsg(int socket, msg_t *msg) {
    char *message = convertMessageToString(msg);
    int return_value = send(socket, message, strlen(message) + 1, 0);
    if (return_value < 0) {
        printf("Couldn't send message: %s\n", message);
        close(socket);
        exit(-1);
    }
}

msg_t *receiveMsg(int socket) {
    char message[1024];
    int return_value = recv(socket, message, sizeof(message), 0);
    if (return_value < 0) {
        printf("Couldn't receive message\n");
        close(socket);
        exit(-1);
    }
    msg_t *msg = convertStringToMessage(createString(message));
    return msg;
}

void closeConnection(int socket) {
    msg_t *msg = newMsg(REQUEST_TO_CLOSE_CONNECTION, NULL, NULL);
    sendMsg(socket, msg);
    close(socket);
    shutdown(socket, 0);
    shutdown(socket, 1);
    shutdown(socket, 2);
}

void closeServer(int socket) {
    msg_t *msg = newMsg(REQUEST_TO_CLOSE_SERVER, NULL, NULL);
    sendMsg(socket, msg);
}