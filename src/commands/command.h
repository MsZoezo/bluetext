
#ifndef BLUETEXT_COMMAND_H
#define BLUETEXT_COMMAND_H


#include <string>
#include <list>
#include "../messageCollection.h"
#include "../programState.h"

class Command {
protected:
    std::string name;
    std::string usage;

public:
    Command(std::string name, std::string usage);

    const std::string& getName() const;
    const std::string& getUsage() const;

    virtual void run(MessageCollection& messageCollection, ProgramState& programState, std::list<std::string> args) = 0;
};


#endif //BLUETEXT_COMMAND_H
