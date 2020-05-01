//
// Created by Aimen Fahmi on 2020-04-30.
//

#include "Tests.h"

int communicationProtocolTest() {
    item_t *item = newItem("aimen", 43, 542.65323, "very good", "https://what", "category");

    msg_t *message1 = newMsg(REQUEST_TO_ADD_NEW_ITEM, ITEM_T, convertItemToString(item));
    msg_t *message2 = newMsg("Some defined command", FLOAT, "435.6546");
    msg_t *message3 = newMsg(REQUEST_TO_CLOSE_SERVER, NULL, NULL);

    char * msg_to_send1 = convertMessageToString(message1);
    char * msg_to_send2 = convertMessageToString(message2);
    char * msg_to_send3 = convertMessageToString(message3);

    msg_t *received_msg1 = convertStringToMessage(msg_to_send1);
    msg_t *received_msg2 = convertStringToMessage(msg_to_send2);
    msg_t *received_msg3 = convertStringToMessage(msg_to_send3);

    printMsg(received_msg1);
    printMsg(received_msg2);
    printMsg(received_msg3);

    return 0;
}

int tokenizationTest() {
    item_t *item = newItem("aimen", 542, 0, NULL, NULL, NULL);
    char *item_as_string = convertItemToString(item);
    char **tokens = getTokens(item_as_string, MESSAGE_DELIMITER);

    int i = 0;
    while (tokens[i] != NULL) {
        printf("%s\n", tokens[i]);
        i++;
    }
    return 0;
}

int main() {
    tokenizationTest();
    return 0;
}
