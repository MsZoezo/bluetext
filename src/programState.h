
#ifndef BLUETEXT_PROGRAMSTATE_H
#define BLUETEXT_PROGRAMSTATE_H


#include <string>
#include "networkables/networkable.h"

class ProgramState {
public:
    std::string name = "Unown";
    std::string type;
    std::optional<Networkable*> networkable = std::nullopt;
};


#endif //BLUETEXT_PROGRAMSTATE_H
