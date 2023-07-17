#include <iostream>
#include "console.h"

Console::Console() {
    // Switch to alternate buffer.
    std::cout << "\x1b[?1049h";
}

Console::~Console() {
    // Switch back to main buffer.
    std::cout << "\x1b[?1049l";
}