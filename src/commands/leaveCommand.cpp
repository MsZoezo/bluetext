
#include "leaveCommand.h"

LeaveCommand::LeaveCommand() : Command("leave", "/leave - Leave a chatroom.") {}

void LeaveCommand::run(MessageCollection &messageCollection, ProgramState &programState, std::list<std::string> args) {
    if(!programState.networkable) {
        messageCollection.push(new Message("You are not in a chatroom currently, unable to leave."));
        return;
    }

    if(programState.type != "client") {
        messageCollection.push(new Message("You are the host, unable to leave."));
        return;
    }

    delete programState.networkable.value();
    programState.networkable = std::nullopt;
    programState.type = "";

    messageCollection.push(new Message("Left the chatroom!"));
}


