
#ifndef BLUETEXT_HOSTCOMMAND_H
#define BLUETEXT_HOSTCOMMAND_H


#include "command.h"

class HostCommand : public Command {
public:
    HostCommand();

    void run(MessageCollection& messageCollection, ProgramState& programState, std::list<std::string> args);
};


#endif //BLUETEXT_HOSTCOMMAND_H
