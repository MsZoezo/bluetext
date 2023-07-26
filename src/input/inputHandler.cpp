
#include "inputHandler.h"

void InputHandler::handleInputEvent(_KEY_EVENT_RECORD event) {
    if(event.wVirtualKeyCode == 8) {
        if(event.dwControlKeyState & LEFT_CTRL_PRESSED) this->inputBuffer->removeWord();
        else this->inputBuffer->remove();

        return;
    }

    if(event.wVirtualKeyCode == 13) {
        std::string string = this->inputBuffer->retrieve();

        this->unhandledStrings.push(string);

        this->inputBuffer->clear();
        return;
    }

    if(event.uChar.AsciiChar < 32 || event.uChar.AsciiChar > 126) return;

    this->inputBuffer->add(event.uChar.AsciiChar);
}

const InputBuffer* InputHandler::getInputBuffer() const {
    return this->inputBuffer;
}

InputHandler::InputHandler(int maxLength) {
    this->inputBuffer = new InputBuffer(maxLength);
}

std::optional<std::string> InputHandler::getUnhandledString() {
    if(this->unhandledStrings.empty()) return std::nullopt;

    std::string string = this->unhandledStrings.front();
    this->unhandledStrings.pop();

    return string;
}