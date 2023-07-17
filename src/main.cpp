#include <iostream>
#include "console.h"

int main() {
    Console console;

    std::cout << "Hello World" << std::endl;

    bool running = true;

    while (running) {
        if(console.shouldQuit()) {
            running = false;
            continue;
        }

        console.handleEvents();
    }

    return 0;
}
