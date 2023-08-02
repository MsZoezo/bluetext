
#ifndef BLUETEXT_COMMANDHANDLER_H
#define BLUETEXT_COMMANDHANDLER_H


#include <map>
#include "command.h"
#include "../programState.h"

class CommandHandler {
private:
    std::map<std::string, Command*> commands;

    MessageCollection& messageCollection;
    ProgramState& programState;

public:
    CommandHandler(MessageCollection& messageCollection, ProgramState& programState);

    CommandHandler& addCommand(Command* command);

    void run(std::string rawString);
};


#endif //BLUETEXT_COMMANDHANDLER_H
