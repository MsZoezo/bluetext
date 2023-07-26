
#ifndef BLUETEXT_INPUTHANDLER_H
#define BLUETEXT_INPUTHANDLER_H


#include <queue>
#include <optional>
#include <windows.h>
#include "inputBuffer.h"

class InputHandler {
private:
    InputBuffer* inputBuffer;
    std::queue<std::string> unhandledStrings;

public:
    InputHandler(int maxLength);

    void handleInputEvent(_KEY_EVENT_RECORD event);

    std::optional<std::string> getUnhandledString();

    const InputBuffer* getInputBuffer() const;
};


#endif //BLUETEXT_INPUTHANDLER_H
