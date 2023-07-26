
#include "networkable.h"


Networkable::Networkable(MessageCollection &messageCollection) : messageCollection{messageCollection} {
    WSADATA wsa;
    WORD version = MAKEWORD(2, 2);

    int result = WSAStartup(version, &wsa);

    if(result != 0) {
        throw std::runtime_error(std::format("WSA Startup failed, Error code -> {}\nCodes can be found here -> https://learn.microsoft.com/en-us/windows/win32/winsock/windows-sockets-error-codes-2", result).c_str());
    }
}

Networkable::~Networkable() {
    WSACleanup();
}