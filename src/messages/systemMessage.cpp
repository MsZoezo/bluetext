//
// Created by Zoezo on 1/15/2023.
//

#include "systemMessage.h"

SystemMessage::SystemMessage(std::string message) {
	this->text = fmt::format("\x1b[38;2;167;199;231m{}\x1b[0m", message);
	this->length = message.length();
}
