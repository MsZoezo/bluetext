#ifndef BLUETEXT_CONSOLE_H
#define BLUETEXT_CONSOLE_H

#include <windows.h>

class Console {
private:
    HANDLE in, out;
    DWORD oldMode;

    bool quitable = false;

    void onKeyEvent(_KEY_EVENT_RECORD event);

public:
    void handleEvents();

    bool shouldQuit();

    Console();
    ~Console();
};


#endif //BLUETEXT_CONSOLE_H
