
#ifndef BLUETEXT_GUESTCLIENT_H
#define BLUETEXT_GUESTCLIENT_H


#include "client.h"
#include "remote.h"

class GuestClient : public Client {
private:
    Remote* remote;

    void receive();

public:
    GuestClient(MessageCollection& messageCollection, ULONGLONG ip);

    void send(Message* message);
    void handle();
};


#endif //BLUETEXT_GUESTCLIENT_H
