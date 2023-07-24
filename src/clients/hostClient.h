
#ifndef BLUETEXT_HOSTCLIENT_H
#define BLUETEXT_HOSTCLIENT_H

#include "client.h"
#include "remote.h"
#include <Objbase.h>

class HostClient : public Client {
private:
    SOCKET hostSocket;
    Remote* remotes[3] = { nullptr };

    void acceptRemote();
    void receive();

public:
    HostClient(MessageCollection& messageCollection);

    void send(Message* message);
    void handle();
};


#endif //BLUETEXT_HOSTCLIENT_H
