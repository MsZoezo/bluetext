
#ifndef BLUETEXT_NETWORKABLE_H
#define BLUETEXT_NETWORKABLE_H

#include <format>
#include <WinSock2.h>
#include <bluetoothapis.h>
#include <ws2bth.h>
#include "../messageCollection.h"

class Networkable {

protected:
    MessageCollection& messageCollection;

    virtual void receive() = 0;

public:
    Networkable(MessageCollection& messageCollection);
    ~Networkable();

    virtual void send(Message* message) = 0;
    virtual void handle() = 0;
};


#endif //BLUETEXT_NETWORKABLE_H
