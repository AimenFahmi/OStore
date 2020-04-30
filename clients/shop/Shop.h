//
// Created by Aimen Fahmi on 2020-04-25.
//

#ifndef OSTORE_SHOP_H
#define OSTORE_SHOP_H

#include "../../util/Common_Libraries.h"
#include "../../data/item/Item.h"
#include "../../communication_protocol/CommunicationProtocol.h"
#include "../../communication_protocol/ConnectionHandler.h"

int shop_socket;

int shop_writeItem(item_t *item);
int shop_increaseCountOfItem(char *item_name, int amount);

#endif //OSTORE_SHOP_H
