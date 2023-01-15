//
// Created by Zoezo on 1/15/2023.
//

#ifndef BLUETEXT_SYSTEMMESSAGE_H
#define BLUETEXT_SYSTEMMESSAGE_H

#include "message.h"

class SystemMessage : public Message {
public:
	SystemMessage(std::string message);
};


#endif //BLUETEXT_SYSTEMMESSAGE_H
