
#ifndef BLUETEXT_COMMANDHANDLER_H
#define BLUETEXT_COMMANDHANDLER_H


#include <map>
#include "commands/command.h"

class CommandHandler {
private:
    std::map<std::string, Command*> commands;

    MessageCollection& messageCollection;

public:
    CommandHandler(MessageCollection& messageCollection);

    void addCommand(Command* command);

    void run(std::string rawString);
};


#endif //BLUETEXT_COMMANDHANDLER_H
