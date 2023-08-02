
#include "command.h"

Command::Command(std::string name, std::string usage) : name{name}, usage{usage} {}

const std::string &Command::getName() const {
    return this->name;
}

const std::string &Command::getUsage() const {
    return this->usage;
}
