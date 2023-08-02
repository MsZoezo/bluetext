
#ifndef BLUETEXT_STOPCOMMAND_H
#define BLUETEXT_STOPCOMMAND_H


#include "command.h"

class StopCommand : public Command {
public:
    StopCommand();

    void run(MessageCollection& messageCollection, ProgramState& programState, std::list<std::string> args);
};


#endif //BLUETEXT_STOPCOMMAND_H
