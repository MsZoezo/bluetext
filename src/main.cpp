#include <format>
#include <iostream>
#include <sstream>
#include "networkables/bluetooth/btServer.h"
#include "console.h"
#include "networkables/bluetooth/btClient.h"
#include "input/inputHandler.h"
#include "commands/commandHandler.h"
#include "programState.h"
#include "commands/nameCommand.h"
#include "commands/hostCommand.h"
#include "commands/stopCommand.h"
#include "commands/clearCommand.h"
#include "commands/JoinCommand.h"

int main(int argc, char** argv) {
    MessageCollection messageCollection;

    InputHandler inputHandler(500);

    ProgramState programState;

    CommandHandler commandHandler(messageCollection, programState);

    commandHandler
        .addCommand(new NameCommand)
        .addCommand(new HostCommand)
        .addCommand(new JoinCommand)
        .addCommand(new StopCommand)
        .addCommand(new ClearCommand);

    Console console(inputHandler, messageCollection);

    bool running = true;

    messageCollection.push(new Message("Welcome to bluetext! type /help for help!"));

    while (running) {
        if(console.shouldQuit()) {
            running = false;
            continue;
        }

         if(programState.networkable) programState.networkable.value()->handle();

        auto string = inputHandler.getUnhandledString();
        if(string) {
            if(string.value().starts_with('/')) {
                commandHandler.run(string.value());
            } else {
                Message* message = new Message(std::format("{} > {}", programState.name, string.value()));

                messageCollection.push(message);
                if(programState.networkable) programState.networkable.value()->send(message);
            }
        }

        console.handleEvents();
        console.render();
    }

    return 0;
}