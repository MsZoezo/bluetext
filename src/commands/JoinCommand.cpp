
#include <sstream>
#include "JoinCommand.h"
#include "../networkables/bluetooth/btClient.h"

JoinCommand::JoinCommand() : Command("join", "/join <ip> - Join a chatroom!") {}

void JoinCommand::run(MessageCollection &messageCollection, ProgramState &programState, std::list<std::string> args) {
    if(programState.networkable) {
        messageCollection.push(new Message("You're already in a chatroom, cannot join."));
        return;
    }

    if(args.empty()) {
        messageCollection.push(new Message("Missing argument for ip, usage: /join <ip>"));
        return;
    }

    ULONGLONG ip;
    std::istringstream iss(args.front());
    iss >> std::hex >> ip;

    try {
        programState.networkable = new BTClient(messageCollection, ip);
        programState.type = "client";
    } catch(std::exception& exception) {
        messageCollection.push(new Message(exception.what()));
    }
}
