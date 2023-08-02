
#include "hostCommand.h"
#include "../networkables/bluetooth/btServer.h"

HostCommand::HostCommand() : Command("host", "/host - Host a chatroom") {}

void HostCommand::run(MessageCollection &messageCollection, ProgramState &programState, std::list<std::string> args) {
    if(programState.networkable) {
        messageCollection.push(new Message("You're already in a chatroom, cannot host."));
        return;
    }

    try {
        programState.networkable = new BTServer(messageCollection);
        programState.type = "server";
    } catch(std::exception& exception) {
        messageCollection.push(new Message(exception.what()));
    }
}
