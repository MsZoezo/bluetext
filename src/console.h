#ifndef BLUETEXT_CONSOLE_H
#define BLUETEXT_CONSOLE_H

#include <windows.h>
#include <vector>
#include "message.h"

class Console {
private:
    HANDLE in, out;
    DWORD oldMode;
    int width, height;

    bool quitable = false;

    std::vector<Message*> messages;
    bool messagesChanged = false;

    void onKeyEvent(_KEY_EVENT_RECORD event);

public:
    void handleEvents();

    bool shouldQuit();
    bool hasMessagesChanged();

    void redrawFull();
    void redrawMessageArea();

    Console();
    ~Console();
};


#endif //BLUETEXT_CONSOLE_H
