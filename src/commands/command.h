
#ifndef BLUETEXT_COMMAND_H
#define BLUETEXT_COMMAND_H


#include <string>
#include "../messageCollection.h"

class Command {
protected:
    std::string name;

public:
    Command(std:: string name);

    const std::string& getName() const;

    virtual void run(MessageCollection& messageCollection, std::vector<std::string> args) = 0;
};


#endif //BLUETEXT_COMMAND_H
