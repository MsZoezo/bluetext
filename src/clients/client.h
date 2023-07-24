
#ifndef BLUETEXT_CLIENT_H
#define BLUETEXT_CLIENT_H

#include <format>
#include <WinSock2.h>
#include <bluetoothapis.h>
#include <ws2bth.h>
#include "../messageCollection.h"

class Client {

protected:
    MessageCollection& messageCollection;

    virtual void receive() = 0;

public:
    Client(MessageCollection& messageCollection);
    ~Client();

    virtual void send(Message* message) = 0;
    virtual void handle() = 0;
};


#endif //BLUETEXT_CLIENT_H
