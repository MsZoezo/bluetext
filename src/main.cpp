#include <iostream>
#include <sstream>
#include "clients/hostClient.h"
#include "console.h"
#include "clients/guestClient.h"

int main(int argc, char** argv) {
    MessageCollection messageCollection;

    Client* client;
    std::string name;

    try {
        if(argc >= 4 && strcmp(argv[1], "guest") == 0) {
            ULONGLONG ip;
            std::istringstream iss(argv[2]);
            iss >> std::hex >> ip;

            name = argv[3];
            client = new GuestClient(messageCollection, ip);
        }
        else if(argc >= 3 && strcmp(argv[1], "host") == 0) {
            client = new HostClient(messageCollection);
            name = argv[2];
        }
        else {
            std::cout << "\x1b[31m" << "usage: host <name> OR guest <ip> <name>" << "\x1b[0m"  << std::endl;
            return 1;
        }
    } catch(std::exception& exception) {
        std::cout << exception.what() << std::endl;
        return -1;
    }

    Console console(messageCollection, name);

    bool running = true;

    messageCollection.push(new Message("Welcome to bluetext!"));

    while (running) {
        if(console.shouldQuit()) {
            running = false;
            continue;
        }

        client->handle();

        auto message = console.getLatest();
        if(message) client->send(message.value());

        console.handleEvents();
        console.render();
    }

    return 0;
}
