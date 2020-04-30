//
// Created by Aimen Fahmi on 2020-04-24.
//

#ifndef OSTORE_CUSTOMER_H
#define OSTORE_CUSTOMER_H

#include "../../util/Common_Libraries.h"
#include "../../communication_protocol/CommunicationProtocol.h"
#include "../../communication_protocol/ConnectionHandler.h"
#include "../../data/item/Item.h"

int customer_socket;

int customer_buyItem(char *item_name, int amount);

#endif //OSTORE_CUSTOMER_H
