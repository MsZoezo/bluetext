#ifndef BLUETEXT_CONSOLE_H
#define BLUETEXT_CONSOLE_H

#include <windows.h>
#include <vector>
#include "message.h"
#include "inputBuffer.h"

class Console {
private:
    HANDLE in, out;
    DWORD oldMode;
    int width, height;

    InputBuffer* inputBuffer;

    bool quitable = false;

    std::vector<Message*> messages;
    bool messagesChanged = false;

    bool resized = false;

    bool inputBufferChanged = false;

    void onKeyEvent(_KEY_EVENT_RECORD event);
    void onResizeEvent(_WINDOW_BUFFER_SIZE_RECORD event);

public:
    void handleEvents();

    bool shouldQuit();
    bool hasMessagesChanged();
    bool hasResized();
    bool hasInputBufferChanged();

    void redrawFull();
    void redrawMessageArea();
    void redrawInputArea();

    Console();
    ~Console();
};


#endif //BLUETEXT_CONSOLE_H
