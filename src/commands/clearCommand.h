
#ifndef BLUETEXT_CLEARCOMMAND_H
#define BLUETEXT_CLEARCOMMAND_H


#include "command.h"

class ClearCommand : public Command {
public:
    ClearCommand();

    void run(MessageCollection& messageCollection, ProgramState& programState, std::list<std::string> args);
};


#endif //BLUETEXT_CLEARCOMMAND_H
