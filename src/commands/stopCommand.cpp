
#include "stopCommand.h"

StopCommand::StopCommand() : Command("stop", "/stop - Stop hosting the chatroom.") {}

void StopCommand::run(MessageCollection &messageCollection, ProgramState &programState, std::list<std::string> args) {
    if(!programState.networkable) {
        messageCollection.push(new Message("You are not in a chatroom currently, unable to stop."));
        return;
    }

    if(programState.type != "server") {
        messageCollection.push(new Message("You are not the host, unable to stop."));
        return;
    }

    delete programState.networkable.value();
    programState.networkable = std::nullopt;
    programState.type = "";

    messageCollection.push(new Message("Stopped hosting the chatroom!"));
}
