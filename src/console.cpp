#include <iostream>
#include <format>
#include "console.h"

Console::Console() {
    this->in = GetStdHandle(STD_INPUT_HANDLE);
    if(in == INVALID_HANDLE_VALUE) throw std::exception("A fatal error occurred while getting the input handle.");

    this->out = GetStdHandle(STD_OUTPUT_HANDLE);
    if(out == INVALID_HANDLE_VALUE) throw std::exception("A fatal error occurred while getting the output handle.");

    if(GetConsoleMode(this->in, &oldMode) == 0) throw std::exception(std::format("A fatal error occurred while getting console mode. Error -> {}", GetLastError()).c_str());

    DWORD mode = ENABLE_WINDOW_INPUT;
    if(SetConsoleMode(this->in, mode) == 0) throw std::exception(std::format("A fatal error occurred while setting console mode. Error -> {}", GetLastError()).c_str());

    // Switch to alternate buffer.
    std::cout << "\x1b[?1049h";
}

Console::~Console() {
    // Switch back to main buffer.
    std::cout << "\x1b[?1049l";

    if(SetConsoleMode(this->in, oldMode) == 0) throw std::exception(std::format("A fatal error occurred while setting console mode. Error -> {}", GetLastError()).c_str());
}

void Console::handleEvents() {
    DWORD numberOfEvents = 0;

    // This is an error but it may be non trivial? should keep track of how many fail in a row...
    if(GetNumberOfConsoleInputEvents(this->in, &numberOfEvents) == 0) return;

    if(numberOfEvents == 0) return;

    INPUT_RECORD buffer[128];
    DWORD read, i;

    ReadConsoleInput(in, buffer, 128, &read);

    for(i = 0; i < read; i++) {
        switch(buffer[i].EventType) {
            case KEY_EVENT:
                this->onKeyEvent(buffer[i].Event.KeyEvent);

                break;

            case WINDOW_BUFFER_SIZE_EVENT:
                break;
        }
    }
}

void Console::onKeyEvent(_KEY_EVENT_RECORD event) {
    if(event.wVirtualKeyCode == 67 && event.dwControlKeyState & LEFT_CTRL_PRESSED) {
        quitable = true;
        return;
    }

    if(event.uChar.AsciiChar >= 32 && event.uChar.AsciiChar <= 126) std::cout << std::format("'{}', {} key event", event.uChar.AsciiChar, event.wVirtualKeyCode) << std::endl;
}

bool Console::shouldQuit() {
    return quitable;
}
