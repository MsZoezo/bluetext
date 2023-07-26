#ifndef BLUETEXT_CONSOLE_H
#define BLUETEXT_CONSOLE_H

#include <windows.h>
#include <vector>
#include "message.h"
#include "input/inputBuffer.h"
#include "messageCollection.h"
#include "input/inputHandler.h"

class Console {
private:
    HANDLE in, out;
    DWORD oldMode;
    int width, height;

    std::string name;

    InputHandler& inputHandler;
    const InputBuffer* inputBuffer;
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

public:
    void handleEvents();

    bool shouldQuit();

    void render(bool force = false);

    Console(InputHandler& inputHandler, MessageCollection& messageCollection, std::string name);
    ~Console();
};


#endif //BLUETEXT_CONSOLE_H
