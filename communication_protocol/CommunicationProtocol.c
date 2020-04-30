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
    char *imgUrl = item->imgUrl;
    char *category = item->category;

    char item_as_string[strlen(name) + amount_length + price_length + strlen(description) + strlen(imgUrl) + strlen(category) + 5 * strlen(MESSAGE_DELIMITER) + 1];
    memset(item_as_string, 0, strlen(item_as_string));

    strcat(item_as_string, name);
    strcat(item_as_string, MESSAGE_DELIMITER);
    strcat(item_as_string, amount);
    strcat(item_as_string, MESSAGE_DELIMITER);
    strcat(item_as_string, price);
    strcat(item_as_string, MESSAGE_DELIMITER);
    strcat(item_as_string, description);
    strcat(item_as_string, MESSAGE_DELIMITER);
    strcat(item_as_string, imgUrl);
    strcat(item_as_string, MESSAGE_DELIMITER);
    strcat(item_as_string, category);

    return createString(item_as_string);
}

item_t *convertStringToItem(char *string) {
    char *delimiters = concat(MESSAGE_DELIMITER, "\n");
    char **tokens = tokenize(string, delimiters);

    /*printf("[name: %s, amount: %s, price: %s, description: %s, imgUrl: %s, category: %s]\n",
            tokens[0], tokens[1], tokens[2], tokens[3], tokens[4], tokens[5]);*/

    int nb_of_tokens = 0;
    while (tokens[nb_of_tokens] != NULL) {nb_of_tokens++;}

    if (nb_of_tokens != 6) {
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
    char *command = message->command;
    char *data_type = message->data_type;
    char *content = message->content;

    string = concat(command, MESSAGE_DELIMITER);
    if (data_type && (strcmp(data_type, ITEM_T) == 0 || strcmp(data_type, STRING) == 0 || strcmp(data_type, INT) == 0 ||
    strcmp(data_type, FLOAT) == 0 || strcmp(data_type, CHAR) == 0 || strcmp(data_type, DOUBLE) == 0 || strcmp(data_type, ACKNOWLEDGMENT) == 0)) {
            string = concat(string, data_type);
            string = concat(string, MESSAGE_DELIMITER);
            string = concat(string, content);
            string = concat(string, END_OF_MESSAGE);
    } else if (data_type == NULL) {
        string = concat(string, END_OF_MESSAGE);
    }

    return string;
}

msg_t *convertStringToMessage(char *message) {
    if (message == NULL) {
        printf("Message is empty\n");
        return NULL;
    }

    char **tokens = tokenize(message, concat(MESSAGE_DELIMITER, "\n"));
    msg_t *msg = malloc_safe_mode(sizeof(msg_t));
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

    return msg;
}

void printMsg(msg_t *msg) {
    printTitle("Message");
    printf("[command: %s, data_type: %s, content: %s]\t\t<=>\t\t%s\n", msg->command, msg->data_type, msg->content, convertMessageToString(msg));
}
