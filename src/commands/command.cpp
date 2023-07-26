
#include "command.h"

Command::Command(std::string name) : name{name} {}

const std::string &Command::getName() const {
    return this->name;
}
