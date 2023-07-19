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
        console.render();
    }

    return 0;
}
