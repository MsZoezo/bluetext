//
// Created by Zoezo on 1/15/2023.
//

#include "errorMessage.h"

ErrorMessage::ErrorMessage(std::string message) {
	this->text = fmt::format("\x1b[38;2;250;160;160m{}\x1b[0m" ,message);
	this->length = message.length();
}
