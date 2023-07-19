#include <iostream>
#include "console.h"

#include <windows.h>

int main() {
    Console console;

    bool running = true;

    while (running) {
        if(console.shouldQuit()) {
            running = false;
            continue;
        }

        console.handleEvents();

        if(console.hasResized()) console.redrawFull();
        if(console.hasMessagesChanged()) console.redrawMessageArea();
        if(console.hasInputBufferChanged()) console.redrawInputArea();
    }

    return 0;
}
