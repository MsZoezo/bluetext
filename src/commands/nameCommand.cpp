
#include <sstream>
#include "nameCommand.h"

NameCommand::NameCommand() : Command("name", "/name <name> - Sets your name.") {}

void NameCommand::run(MessageCollection &messageCollection, ProgramState &programState, std::list<std::string> args) {
    if(args.empty()) {
        messageCollection.push(new Message("Missing argument for name, usage: /name <name>"));
    }

    std::stringstream name;

    while (!args.empty()) {
        name << args.front();
        args.pop_front();

        if(!args.empty()) name << ' ';
    }

    programState.name = name.str();
    messageCollection.push(new Message(std::format("Set name to '{}'", name.str())));
}
