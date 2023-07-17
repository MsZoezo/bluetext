
#include "message.h"

const std::string &Message::getContent() const {
    return content;
}

int Message::getLength() {
    return content.length();
}

Message::Message(std::string content) : content{content} {}
