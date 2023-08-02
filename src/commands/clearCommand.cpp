
#include "clearCommand.h"

ClearCommand::ClearCommand() : Command("clear", "/clear - Clears all messages."){}

void ClearCommand::run(MessageCollection &messageCollection, ProgramState &programState, std::list<std::string> args) {
    messageCollection.clear();

    messageCollection.push(new Message("Cleared all messages!"));
}
