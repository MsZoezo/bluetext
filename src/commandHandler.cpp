
#include <sstream>
#include "commandHandler.h"

void CommandHandler::addCommand(Command *command) {
    this->commands.insert(std::make_pair(command->getName(), command));
}

void CommandHandler::run(std::string rawString) {
    std::vector<std::string> args;


    std::stringstream stream(rawString);
    std::string word;
    std::string commandName;

    getline(stream, commandName, ' ');

    while (!stream.eof()) {
        getline(stream, word, ' ');
        args.push_back(word);
    }

    commandName.erase(0, 1);

    if(!this->commands.contains(commandName)) {
        this->messageCollection.push(new Message("This Command doesn't exist!"));
        return;
    }

    Command* command = this->commands.find(commandName)->second;

    command->run(this->messageCollection, args);
}

CommandHandler::CommandHandler(MessageCollection& messageCollection) : messageCollection{messageCollection} {}
