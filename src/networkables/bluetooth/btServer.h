
#ifndef BLUETEXT_BTSERVER_H
#define BLUETEXT_BTSERVER_H

#include "../networkable.h"
#include "../remote.h"
#include <Objbase.h>
#include <format>

class BTServer : public Networkable {
private:
    SOCKET hostSocket;
    Remote* remotes[3] = { nullptr };

    void acceptRemote();
    void receive();

public:
    BTServer(MessageCollection& messageCollection);

    void send(Message* message);
    void handle();
};


#endif //BLUETEXT_BTSERVER_H
