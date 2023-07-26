
#include "btClient.h"

BTClient::BTClient(MessageCollection &messageCollection, ULONGLONG ip) : Networkable(messageCollection) {
    int family = AF_BTH;
    int type = SOCK_STREAM;
    int protocol = BTHPROTO_RFCOMM;

    SOCKET guestSocket = socket(family, type, protocol);

    if(guestSocket == INVALID_SOCKET) throw std::runtime_error(std::format("Initializing guest socket failed. Error code -> {}", WSAGetLastError()).c_str());

    SOCKADDR_BTH hint;
    memset(&hint, 0, sizeof hint);
    hint.addressFamily = AF_BTH;
    hint.port = 25;
    hint.btAddr = BTH_ADDR(ip);
    hint.serviceClassId = RFCOMM_PROTOCOL_UUID;

    if(connect(guestSocket, (sockaddr *) &hint, sizeof hint) == SOCKET_ERROR) throw std::runtime_error(std::format("Failed to connect. Error code -> {}", WSAGetLastError()).c_str());

    this->messageCollection.push(new Message("Connected to host!"));

    unsigned long ul = 1;

    if(ioctlsocket(guestSocket, FIONBIO, (unsigned long *) &ul) == SOCKET_ERROR) throw std::runtime_error(std::format("An error occured while setting the socket to non-blocking, error code -> {}", WSAGetLastError()).c_str());


    this->remote = new Remote(guestSocket, 999);
}

void BTClient::send(Message* message) {
    if(this->remote == nullptr) return;

    this->remote->sendQueue.push(message);
}

void BTClient::receive() {
    if(this->remote == nullptr) return;

    if(this->remote->receiveQueue.empty()) return;
    this->messageCollection.push(this->remote->receiveQueue.front());
    this->remote->receiveQueue.pop();
}

void BTClient::handle() {
    if(this->remote == nullptr) return;

    if(!this->remote->isConnected()) {
        this->messageCollection.push(new Message("Connection with the host lost. you're on your own..."));
        delete this->remote;
        this->remote = nullptr;

        return;
    }

    this->receive();

    fd_set fdread, fdwrite;
    int ret;

    FD_ZERO(&fdread);
    FD_ZERO(&fdwrite);

    FD_SET(this->remote->getSocket(), &fdread);
    FD_SET(this->remote->getSocket(), &fdwrite);

    ret = select(0, &fdread, &fdwrite, NULL, NULL);

    if(ret == SOCKET_ERROR) {
        this->messageCollection.push(new Message(std::format("Something went wrong with select(), error code -> {}", WSAGetLastError())));
        return;
    }

    if(ret <= 0) return;

    if(FD_ISSET(this->remote->getSocket(), &fdread)) this->remote->handleReceive();
    if(FD_ISSET(this->remote->getSocket(), &fdwrite)) this->remote->handleSend();

}
