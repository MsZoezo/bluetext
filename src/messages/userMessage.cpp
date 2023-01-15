//
// Created by Zoezo on 1/15/2023.
//

#include <fmt/format.h>
#include "userMessage.h"

UserMessage::UserMessage(std::string message, std::string user) {
	this->text = fmt::format("{} > {}", user, message);
	this->length = this->text.length();
}
