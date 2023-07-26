
#ifndef BLUETEXT_BTCLIENT_H
#define BLUETEXT_BTCLIENT_H


#include "../networkable.h"
#include "../remote.h"

class BTClient : public Networkable {
private:
    Remote* remote;

    void receive();

public:
    BTClient(MessageCollection& messageCollection, ULONGLONG ip);

    void send(Message* message);
    void handle();
};


#endif //BLUETEXT_BTCLIENT_H
