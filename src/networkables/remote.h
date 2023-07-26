
#ifndef BLUETEXT_REMOTE_H
#define BLUETEXT_REMOTE_H

#include <winsock2.h>
#include <queue>
#include "../message.h"

class Remote {
private:
    SOCKET remoteSocket;
    int id;

    bool connected = true;

public:
    Remote(SOCKET remoteSocket, int id);
    ~Remote();

    std::queue<Message*> sendQueue;
    std::queue<Message*> receiveQueue;

    void handleSend();
    void handleReceive();

    SOCKET getSocket();
    bool isConnected();
};


#endif //BLUETEXT_REMOTE_H
