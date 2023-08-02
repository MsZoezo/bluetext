
#include <sstream>
#include "commandHandler.h"

CommandHandler& CommandHandler::addCommand(Command *command) {
    this->commands.insert(std::make_pair(command->getName(), command));

    return *this;
}

void CommandHandler::run(std::string rawString) {
    std::list<std::string> args;


    std::stringstream stream(rawString);
    std::string word;
    std::string commandName;

    getline(stream, commandName, ' ');

    while (!stream.eof()) {
        getline(stream, word, ' ');
        args.push_back(word);
    }

    commandName.erase(0, 1);

    if(commandName == "help") {
        this->messageCollection.push(new Message("--- List of all commands ---"));
        for(auto& command : this->commands) this->messageCollection.push(new Message(command.second->getUsage()));
        return;
    }

    if(!this->commands.contains(commandName)) {
        this->messageCollection.push(new Message("This Command doesn't exist!"));
        return;
    }

    Command* command = this->commands.find(commandName)->second;

    command->run(this->messageCollection, programState, args);
}

CommandHandler::CommandHandler(MessageCollection& messageCollection, ProgramState& programState) : messageCollection{messageCollection}, programState{programState} {}
