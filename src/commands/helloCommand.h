
#ifndef BLUETEXT_HELLOCOMMAND_H
#define BLUETEXT_HELLOCOMMAND_H


#include "command.h"

class HelloCommand : public Command {
public:
    HelloCommand();

    void run(MessageCollection& messageCollection, std::vector<std::string> args);
};


#endif //BLUETEXT_HELLOCOMMAND_H
