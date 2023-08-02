
#ifndef BLUETEXT_LEAVECOMMAND_H
#define BLUETEXT_LEAVECOMMAND_H


#include "command.h"

class LeaveCommand : public Command {
public:
    LeaveCommand();

    void run(MessageCollection& messageCollection, ProgramState& programState, std::list<std::string> args);
};


#endif //BLUETEXT_LEAVECOMMAND_H
