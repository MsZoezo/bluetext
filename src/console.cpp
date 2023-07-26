#include <iostream>
#include <format>
#include <optional>
#include <cmath>
#include "console.h"

Console::Console(MessageCollection& messageCollection, std::string name) : messageCollection{messageCollection}, name{name} {
    this->in = GetStdHandle(STD_INPUT_HANDLE);
    if(in == INVALID_HANDLE_VALUE) throw std::runtime_error("A fatal error occurred while getting the input handle.");

    this->out = GetStdHandle(STD_OUTPUT_HANDLE);
    if(out == INVALID_HANDLE_VALUE) throw std::runtime_error("A fatal error occurred while getting the output handle.");

    if(GetConsoleMode(this->in, &oldMode) == 0) throw std::runtime_error(std::format("A fatal error occurred while getting console mode. Error -> {}", GetLastError()).c_str());

    DWORD mode = ENABLE_WINDOW_INPUT;
    if(SetConsoleMode(this->in, mode) == 0) throw std::runtime_error(std::format("A fatal error occurred while setting console mode. Error -> {}", GetLastError()).c_str());

    CONSOLE_SCREEN_BUFFER_INFO info;
    if(GetConsoleScreenBufferInfo(this->out, &info) == 0) throw std::runtime_error(std::format("A fatal error occurred while trying to get console screen buffer info. Error -> {}", GetLastError()).c_str());

    this->width = info.srWindow.Right + 1;
    this->height = info.srWindow.Bottom + 1;

    // Switch to alternate buffer.
    std::cout << "\x1b[?1049h";

    this->inputBuffer = new InputBuffer(100);

    this->render(true);
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

    std::optional<WINDOW_BUFFER_SIZE_RECORD> resizeEvent = std::nullopt;

    ReadConsoleInput(in, buffer, 128, &read);

    for(i = 0; i < read; i++) {
        switch(buffer[i].EventType) {
            case KEY_EVENT:
                this->onKeyEvent(buffer[i].Event.KeyEvent);

                break;

            case WINDOW_BUFFER_SIZE_EVENT:
                resizeEvent = buffer[i].Event.WindowBufferSizeEvent;
                break;
        }
    }

    if(resizeEvent) this->onResizeEvent(resizeEvent.value());
}

void Console::onKeyEvent(_KEY_EVENT_RECORD event) {
    if(event.wVirtualKeyCode == 67 && event.dwControlKeyState & LEFT_CTRL_PRESSED) {
        quitable = true;
        return;
    }

    if (!event.bKeyDown) return;

    if(event.wVirtualKeyCode == 8) {
        this->inputBuffer->remove();
        this->inputBufferChanged = true;
        return;
    }

    if(event.wVirtualKeyCode == 13) {
        Message* message = new Message(std::format("{} > {}", this->name, this->inputBuffer->retrieve()));
        latest = message;

        this->messageCollection.push(message);
        this->inputBuffer->clear();
        this->inputBufferChanged = true;
        return;
    }

    if(event.uChar.AsciiChar < 32 || event.uChar.AsciiChar > 126) return;

    this->inputBuffer->add(event.uChar.AsciiChar);
    this->inputBufferChanged = true;
}

void Console::onResizeEvent(_WINDOW_BUFFER_SIZE_RECORD event) {
    this->width = event.dwSize.X;
    this->height = event.dwSize.Y;

    this->resized = true;
}

bool Console::shouldQuit() {
    return quitable;
}

void Console::render(bool force) {
    if(this->resized || force) this->renderDecorations();
    if(this->messageCollection.hasChanged() || this->resized || force) this->renderMessageArea();
    if(this->resized || this->inputBufferChanged || force) this->renderInputArea();

    this->resized = false, this->inputBufferChanged = false;
}

void Console::renderDecorations() {
    this->moveTo(1, 1);
    std::cout<< std::string(this->width, 223);

    std::string name = "BlueText";
    int pos = this->width / 2 - (name.length() + 2) / 2;

    this->moveTo(pos, 1);
    std::cout << (char) 221 << "\x1b[1m\x1b[38;2;162;193;224m" << name << "\x1b[0m" << (char) 222;

    this->moveTo(1, this->height - 1);
    std::cout << std::string(this->width, 223);
}

void Console::renderMessageArea() {
    this->deleteLines(1, 2, this->height - 3);
    this->moveTo(1, 2);

    std::string printable;
    int index = this->messageCollection.size() - 1;
    int lines = this->height - 3;

    while(lines > 0 && index >= 0) {
        Message* message = this->messageCollection[index];

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

    std::cout << printable;
}

void Console::renderInputArea() {
    bool typed = false;
    std::string buffer = "Start typing...";

    std::string lengthText = std::format(" {}/{} ", this->inputBuffer->getLength(), this->inputBuffer->getMaxLength());
    int textPos = this->width - lengthText.length();

    if(this->inputBuffer->getLength() != 0) {
        buffer = this->inputBuffer->retrieve(this->width - lengthText.length() - 2);
        typed = true;
    }

    this->deleteLines(1, this->height, 1);
    this->moveTo(1, this->height);

    if(!typed) std::cout << "\x1b[38;2;170;170;170m" << buffer << "\x1b[0m";
    else std::cout << buffer;

    this->moveTo(textPos, this->height);
    std::cout << "\x1b[7m" << lengthText << "\x1b[0m";
}

void Console::deleteLines(int x, int y, int lines) {
    std::cout << std::format("\x1b[{0};{1}H\x1b[{2}M\x1b[{2}L", y, x, lines);
}

void Console::moveTo(int x, int y) {
    std::cout << std::format("\x1b[{};{}H", y, x);
}

std::optional<Message*> Console::getLatest() {
    if(!this->latest) return std::nullopt;

    std::optional<Message*> message = this->latest;
    this->latest = std::nullopt;

    return message;
}
