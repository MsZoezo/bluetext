//
// Created by Zoezo on 1/15/2023.
//

#include "systemMessage.h"

SystemMessage::SystemMessage(std::string message) {
	this->text = message;
	this->length = this->text.length();
}
