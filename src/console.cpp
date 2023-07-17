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

    CONSOLE_SCREEN_BUFFER_INFO info;
    if(GetConsoleScreenBufferInfo(this->out, &info) == 0) throw std::exception(std::format("A fatal error occurred while trying to get console screen buffer info. Error -> {}", GetLastError()).c_str());

    this->width = info.srWindow.Right + 1;
    this->height = info.srWindow.Bottom + 1;

    // Switch to alternate buffer.
    std::cout << "\x1b[?1049h";

    this->redrawFull();
}

Console::~Console() {
    // Switch back to main buffer.
    std::cout << "\x1b[?1049l";

    if(SetConsoleMode(this->in, oldMode) == 0) std::cout << std::format("A fatal error occurred while setting console mode. Error -> {}", GetLastError()).c_str() << std::endl;
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

    if(event.uChar.AsciiChar < 32 || event.uChar.AsciiChar > 126 || !event.bKeyDown) return;

    this->messages.push_back(new Message(std::format("'{}', {} pressed", event.uChar.AsciiChar, event.wVirtualKeyCode)));
    this->messagesChanged = true;
}

void Console::redrawFull() {
    // Move to the top left corner.
    std::cout << "\x1b[1;1H";
    std::cout << std::string(this->width, 223) << std::endl;

    std::string name = "BlueText";
    int pos = this->width / 2 - (name.length() + 2) / 2;

    std::cout << std::format("\x1b[1;{}H", pos) << (char) 221 << name << (char) 222 << std::endl;

    std::cout << std::format("\x1b[{};1H", this->height - 1);
    std::cout << std::string(this->width, 223) << std::endl;

    this->redrawMessageArea();
}

void Console::redrawMessageArea() {
    // First we 'clear' the area
    // We calculate how much space we need / can handle
    // we print that section
    try {
        int capacity = this->width * (this->height - 3);

        std::cout << std::format("\x1b[2;1H{}", std::string(capacity, ' '));

        std::string printable;
        int index = this->messages.size() - 1;

        int lines = this->height - 3;
        while(lines > 0 && index >= 0) {
            Message* message = messages.at(index);

            int length = message->getLength();
            int usedLines = ceil((double) length / (double) width);

            std::string content;

            if(lines - usedLines < 0) content = message->getContent().substr(usedLines - lines * width);
            else content = message->getContent();

            if(length % width != 0) printable.insert(0, "\n");
            printable.insert(0, content);

            index--;
            lines = lines - usedLines;
        }

        std::cout << "\x1b[2;1H" << printable;

    } catch(std::exception& exception) {
        std::cout << exception.what();
    }
}

bool Console::shouldQuit() {
    return quitable;
}

bool Console::hasMessagesChanged() {
    if(!messagesChanged) return false;

    this->messagesChanged = false;
    return true;
}
