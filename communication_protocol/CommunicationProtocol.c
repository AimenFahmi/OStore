//
// Created by Aimen Fahmi on 2020-04-21.
//

#include "CommunicationProtocol.h"

char *convertItemToString(item_t *item) {
    int amount_length = 12;
    int price_length = 21;
    char amount[amount_length];
    char price[price_length];

    char *name = item->name;
    sprintf(amount, "%d", item->amount);
    sprintf(price, "%0.2f", item->price);
    char *description = item->description;
    if (description == NULL) {
        description = "empty";
    }
    char *imgUrl = item->imgUrl;
    if (imgUrl == NULL) {
        imgUrl = "empty";
    }
    char *category = item->category;
    if (category == NULL) {
        category = "empty";
    }

    char *item_as_string = NULL;

    item_as_string = concat(item_as_string, name);
    item_as_string = concat(item_as_string, MESSAGE_DELIMITER);
    item_as_string = concat(item_as_string, amount);
    item_as_string = concat(item_as_string, MESSAGE_DELIMITER);
    item_as_string = concat(item_as_string, price);
    item_as_string = concat(item_as_string, MESSAGE_DELIMITER);
    item_as_string = concat(item_as_string, description);
    item_as_string = concat(item_as_string, MESSAGE_DELIMITER);
    item_as_string = concat(item_as_string, imgUrl);
    item_as_string = concat(item_as_string, MESSAGE_DELIMITER);
    item_as_string = concat(item_as_string, category);

    return createString(item_as_string);
}

item_t *convertStringToItem(char *string) {
    char **tokens = getTokens(string, MESSAGE_DELIMITER);

    int nb_of_tokens = 0;
    while (tokens[nb_of_tokens] != NULL) {nb_of_tokens++;}

    if (nb_of_tokens != 6) {
        printf("[-] Couldn't tokenize because nb_of_tokens = %d for: %s\n", nb_of_tokens, string);
        printf("[name: %s, amount: %s, price: %s, description: %s, imgUrl: %s, category: %s]\n",
                tokens[0], tokens[1], tokens[2], tokens[3], tokens[4], tokens[5]);
        return NULL;
    }

    char *name = tokens[0];
    int amount = atoi(tokens[1]);
    float price = atof(tokens[2]);
    char *description = tokens[3];
    char *imgUrl = tokens[4];
    char *category = tokens[5];

    return newItem(name, amount, price, description, imgUrl, category);
}

char *convertMessageToString(msg_t *message) {
    if (message == NULL) {
        printf("Message is empty\n");
        return NULL;
    } else if (message->command == NULL) {
        printf("Message '%s' contains no command\n", message->content);
        return NULL;
    }

    char *string = NULL;

    char length[12];
    sprintf(length, "%.4d", message->length);
    char *command = message->command;
    char *data_type = message->data_type;
    char *content = message->content;

    string = concat(length, MESSAGE_DELIMITER);
    string = concat(string, command);
    string = concat(string, MESSAGE_DELIMITER);
    if (data_type != NULL && (strcmp(data_type, ITEM_T) == 0 || strcmp(data_type, STRING) == 0 || strcmp(data_type, INT) == 0 ||
    strcmp(data_type, FLOAT) == 0 || strcmp(data_type, CHAR) == 0 || strcmp(data_type, DOUBLE) == 0 || strcmp(data_type, ACKNOWLEDGMENT) == 0)) {
            string = concat(string, data_type);
            string = concat(string, MESSAGE_DELIMITER);
            string = concat(string, content);
    } else {
        string = concat(string, MESSAGE_DELIMITER);
    }

    return string;
}

msg_t *convertStringToMessage(char *message) {
    if (message == NULL) {
        printf("Message is empty\n");
        return NULL;
    }

    char **tokens = getTokens(message, MESSAGE_DELIMITER);
    msg_t *msg = malloc_safe_mode(sizeof(msg_t));
    msg->length = 5+strlen(message);
    msg->command = tokens[0];

    if (tokens[1] != NULL) {
        msg->data_type = tokens[1];
        char *content = NULL;
        int i = 2;
        while (tokens[i] != NULL) {
            if (tokens[i+1] == NULL) {
                content = concat(content, tokens[i]);
            } else {
                content = concat(content, tokens[i]);
                content = concat(content, MESSAGE_DELIMITER);
            }
            i++;
        }
        msg->content = content;
    } else {
        msg->data_type = NULL;
        msg->content = NULL;
    }

    return msg;
}

msg_t *newMsg(char *command, char *data_type, char *content) {
    msg_t *msg = malloc_safe_mode(sizeof(msg_t));

    msg->command = createString(command);
    msg->data_type = createString(data_type);
    msg->content = createString(content);

    int command_length = msg->command == NULL ? 0 : strlen(msg->command);
    int data_type_length = msg->data_type == NULL ? 0 : strlen(msg->data_type);
    int content_length = msg->content == NULL ? 0 : strlen(msg->content);

    msg->length = content_length + data_type_length + command_length + 7;

    return msg;
}

// Returns -1 if it's not a proper message and 0 if it is
int isMessage(msg_t *msg) {
    if (msg == NULL) {return -1;}
    if (msg->length == 0 || msg->length > 10000 || msg->command == NULL) { return -1;}

    if (strcmp(msg->data_type, ITEM_T) == 0) {
        if (msg->content == NULL) { return -1;}
        char **tokens = getTokens(msg->content, MESSAGE_DELIMITER);
        if (tokens[0] == NULL || strcmp(tokens[0], "empty") == 0) { return -1;}
        int nb_of_tokens = -1;
        while (tokens[++nb_of_tokens] != NULL);
        if (nb_of_tokens < NB_TOKENS_IN_ITEM) { return -1;}
    }

    return 0;
}

void printMsg(msg_t *msg) {
    printTitle("Message");
    printf("[length: %d, command: %s, data_type: %s, content: %s]\t\t<=>\t\t%s\n", msg->length, msg->command, msg->data_type, msg->content, convertMessageToString(msg));
}
