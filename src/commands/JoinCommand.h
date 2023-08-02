
#ifndef BLUETEXT_JOINCOMMAND_H
#define BLUETEXT_JOINCOMMAND_H


#include "command.h"

class JoinCommand : public Command {
public:
    JoinCommand();

    void run(MessageCollection& messageCollection, ProgramState& programState, std::list<std::string> args);
};



#endif //BLUETEXT_JOINCOMMAND_H
