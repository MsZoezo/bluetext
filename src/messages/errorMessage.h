//
// Created by Zoezo on 1/15/2023.
//

#ifndef BLUETEXT_ERRORMESSAGE_H
#define BLUETEXT_ERRORMESSAGE_H

#include "message.h"
#include <fmt/format.h>

class ErrorMessage: public Message {
public:
	ErrorMessage(std::string message);
};


#endif //BLUETEXT_ERRORMESSAGE_H
