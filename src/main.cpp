#include <format>
#include <iostream>
#include <sstream>
#include "networkables/bluetooth/btServer.h"
#include "console.h"
#include "networkables/bluetooth/btClient.h"
#include "input/inputHandler.h"
#include "commandHandler.h"
#include "commands/helloCommand.h"

int main(int argc, char** argv) {
    MessageCollection messageCollection;

    InputHandler inputHandler(500);

    CommandHandler commandHandler(messageCollection);
    commandHandler.addCommand(new HelloCommand);

    Networkable* networkable;
    std::string name;

    try {
        if(argc >= 4 && strcmp(argv[1], "guest") == 0) {
            ULONGLONG ip;
            std::istringstream iss(argv[2]);
            iss >> std::hex >> ip;

            name = argv[3];
            networkable = new BTClient(messageCollection, ip);
        }
        else if(argc >= 3 && strcmp(argv[1], "host") == 0) {
            networkable = new BTServer(messageCollection);
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

    Console console(inputHandler, messageCollection, name);

    bool running = true;

    messageCollection.push(new Message("Welcome to bluetext!"));

    while (running) {
        if(console.shouldQuit()) {
            running = false;
            continue;
        }

        networkable->handle();

        auto string = inputHandler.getUnhandledString();
        if(string) {
            if(string.value().starts_with('/')) {
                commandHandler.run(string.value());
            } else {
                Message* message = new Message(std::format("{} > {}", name, string.value()));

                messageCollection.push(message);
                networkable->send(message);
            }
        }

        console.handleEvents();
        console.render();
    }

    return 0;
}