
#ifndef BLUETEXT_NAMECOMMAND_H
#define BLUETEXT_NAMECOMMAND_H


#include "command.h"

class NameCommand : public Command {
public:
    NameCommand();

    void run(MessageCollection& messageCollection, ProgramState& programState, std::list<std::string> args);
};


#endif //BLUETEXT_NAMECOMMAND_H
