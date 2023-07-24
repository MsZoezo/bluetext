
#include "remote.h"

Remote::Remote(SOCKET remoteSocket, int id) : remoteSocket{remoteSocket}, id{id} {}

Remote::~Remote() {
    shutdown(this->remoteSocket, 0);
}

void Remote::handleSend() {
    if(this->sendQueue.empty() || !this->connected) return;

    Message* message = this->sendQueue.front();

    send(this->remoteSocket, message->getContent().c_str(), message->getLength(), 0);
    this->sendQueue.pop();
}

void Remote::handleReceive() {
    if(!this->connected) return;

    char buffer[512];
    int received = 0;

    received = recv(this->remoteSocket, buffer, 512, 0);

    if(received == SOCKET_ERROR) {
        this->receiveQueue.push(new Message("Error while receiving data."));
    } else if(received == 0) {
        this->connected = false;
    } else {;
        this->receiveQueue.push(new Message(std::string(buffer, received)));
    }
}

SOCKET Remote::getSocket() {
    return this->remoteSocket;
}

bool Remote::isConnected() {
    return this->connected;
}
