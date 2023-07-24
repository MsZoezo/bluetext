#ifndef BLUETEXT_CONSOLE_H
#define BLUETEXT_CONSOLE_H

#include <windows.h>
#include <vector>
#include "message.h"
#include "inputBuffer.h"
#include "messageCollection.h"

class Console {
private:
    HANDLE in, out;
    DWORD oldMode;
    int width, height;

    std::string name;

    InputBuffer* inputBuffer;
    MessageCollection& messageCollection;

    bool quitable = false;

    bool resized = false;

    bool inputBufferChanged = false;

    void onKeyEvent(_KEY_EVENT_RECORD event);
    void onResizeEvent(_WINDOW_BUFFER_SIZE_RECORD event);

    void renderDecorations();
    void renderMessageArea();
    void renderInputArea();

    void deleteLines(int x, int y, int lines);
    void moveTo(int x, int y);

    std::optional<Message*> latest = std::nullopt;

public:
    void handleEvents();

    bool shouldQuit();

    void render(bool force = false);

    Console(MessageCollection& messageCollection, std::string name);
    ~Console();

    std::optional<Message*> getLatest();
};


#endif //BLUETEXT_CONSOLE_H
