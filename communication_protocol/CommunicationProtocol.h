//
// Created by Aimen Fahmi on 2020-04-21.
//

#ifndef OSTORE_COMMUNICATIONPROTOCOL_H
#define OSTORE_COMMUNICATIONPROTOCOL_H

#include "../util/Common_Libraries.h"
#include "../data/item/Item.h"

/** Commands **/
#define REQUEST_TO_BUY_ITEM "RTBI"
#define REQUEST_TO_ADD_NEW_ITEM "RTANI"
#define REQUEST_TO_INCREASE_COUNT_OF_ITEM "RTICOI"
#define REQUEST_TO_CLOSE_SERVER "RTCS"
#define REQUEST_TO_CLOSE_CONNECTION "RTCC"

/** Acknowledgments **/
#define SUCCESS "SUCCESS"
#define FAILURE "FAILURE"
#define ITEM_STOCK_IS_UNSUFFICIENT "ISIU"
#define ITEM_NOT_FOUND "INF"
#define ITEM_STOCK_IS_FULL "ISIF"
#define MSG_IN_WRONG_FORMAT "MNU"

/** Data types **/
#define ITEM_T "item_t"
#define END_OF_MESSAGE "|"
#define STRING "s"
#define INT "i"
#define CHAR "c"
#define FLOAT "f"
#define DOUBLE "d"
#define ACKNOWLEDGMENT "ack"

#define MESSAGE_DELIMITER ">"
#define NB_TOKENS_IN_ITEM 6
#define PORT "9999"

typedef struct {
    int length; // length of the message
    char *command; // type of request
    char *data_type; // string, int, float,...
    char *content; // the actual content of the message
} msg_t;

msg_t *newMsg(char *command, char *data_type, char *content);
void printMsg(msg_t *msg);

char *convertItemToString(item_t *item);
item_t *convertStringToItem(char *string);

char *convertMessageToString(msg_t *message);
msg_t *convertStringToMessage(char *string);

int isMessage(msg_t *msg);

#endif //OSTORE_COMMUNICATIONPROTOCOL_H
