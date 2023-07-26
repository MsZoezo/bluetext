
#include <format>
#include "helloCommand.h"

HelloCommand::HelloCommand() : Command("hello") {}

void HelloCommand::run(MessageCollection &messageCollection, std::vector<std::string> args) {
    if(args.empty()) {
        messageCollection.push(new Message("Hello unknown person!"));
        return;
    }
    messageCollection.push(new Message(std::format("Hello {}!", args.front())));
}

