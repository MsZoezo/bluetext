//
// Created by Zoezo on 1/15/2023.
//

#ifndef BLUETEXT_USERMESSAGE_H
#define BLUETEXT_USERMESSAGE_H

#include "message.h"

class UserMessage: public Message {
public:
	UserMessage(std::string message, std::string user);
};


#endif //BLUETEXT_USERMESSAGE_H
