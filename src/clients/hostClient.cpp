
#include "hostClient.h"

HostClient::HostClient(MessageCollection& messageCollection) : Client(messageCollection) {
    int family = AF_BTH;
    int type = SOCK_STREAM;
    int protocol = BTHPROTO_RFCOMM;

    this->hostSocket = socket(family, type, protocol);

    if(this->hostSocket == INVALID_SOCKET) throw std::exception(std::format("Initializing host socket failed. Error code -> {}", WSAGetLastError()).c_str());

    SOCKADDR_BTH hint;
    int size = sizeof hint;
    memset(&hint, 0, size);
    hint.addressFamily = AF_BTH;
    hint.port = 25;
    hint.serviceClassId = RFCOMM_PROTOCOL_UUID;

    if(bind(hostSocket, (sockaddr*) &hint, size) == SOCKET_ERROR) {
        int errorCode = WSAGetLastError();
        std::string errorMessage;

        switch(errorCode) {
            case 10050:
                errorMessage = "Failed to bind host socket, it seems your bluetooth is disabled.";
                break;

            default:
                errorMessage = std::format("Failed to bind host socket. Error code -> {}", errorCode);
        }

        throw std::exception(errorMessage.c_str());
    }

    if(listen(hostSocket, SOMAXCONN) == SOCKET_ERROR) throw std::exception(std::format("Failed to listen on host socket. Error code -> {}", WSAGetLastError()).c_str());
    if(getsockname(hostSocket, (sockaddr*) &hint, &size) == SOCKET_ERROR) throw std::exception(std::format("Failed to retrieve address. Error code -> {}", WSAGetLastError()).c_str());

    GUID guid;
    CoCreateGuid(&guid);

    CSADDR_INFO addrInfo = {0};
    addrInfo.LocalAddr.lpSockaddr = (sockaddr*) &hint;
    addrInfo.LocalAddr.iSockaddrLength = size;
    addrInfo.iSocketType = SOCK_STREAM;
    addrInfo.iProtocol = BTHPROTO_RFCOMM;

    WSAQUERYSETW wsaQuery = {0};
    wsaQuery.dwSize = sizeof(WSAQUERYSETW);
    wsaQuery.lpszServiceInstanceName = (LPWSTR) L"BlueText Service"; // Can be anything
    wsaQuery.lpszComment = (LPWSTR) L"Bluetooth communication"; //Can be anything
    wsaQuery.lpServiceClassId = &guid;
    wsaQuery.dwNameSpace = NS_BTH;
    wsaQuery.dwNumberOfCsAddrs = 1;
    wsaQuery.lpcsaBuffer = &addrInfo;


    WSASetServiceW(&wsaQuery, RNRSERVICE_REGISTER, 0);

    unsigned long ul = 1;

    if(ioctlsocket(hostSocket, FIONBIO, (unsigned long *) &ul) == SOCKET_ERROR) throw std::exception(std::format("An error occured while setting the socket to non-blocking, error code -> {}", WSAGetLastError()).c_str());

    this->messageCollection.push(new Message(std::format("Ready for connections, ip is {:#016X}", hint.btAddr)));
}

void HostClient::send(Message* message) {
    for(auto remote : this->remotes) {
        if(remote == nullptr) continue;

        remote->sendQueue.push(message);
    }
}

void HostClient::receive() {
    for(auto remote : this->remotes) {
        if (remote == nullptr) continue;

        if(remote->receiveQueue.empty()) return;
        this->messageCollection.push(remote->receiveQueue.front());
        remote->receiveQueue.pop();
    }
}

void HostClient::acceptRemote() {
    // 1. check for an empty spot in remotes array
    // 2. try to accept a new connection
    // 3. initialize remote instance
    int index = 0;
    bool placeFound = false;

    for(index; index < 3; index++) {
        if(this->remotes[index] != nullptr) continue;

        placeFound = true;
        break;
    }

    if(!placeFound) return;

    SOCKET remoteSocket = accept(this->hostSocket, NULL, 0);

    if(remoteSocket == INVALID_SOCKET) {
        int errorCode = WSAGetLastError();

        switch(errorCode) {
            case 10035:
                return;

            default:
                this->messageCollection.push(new Message("An error occured with someone trying to join! woopsie?"));
                return;
        }
    }

    this->remotes[index] = new Remote(remoteSocket, 999);
    this->messageCollection.push(new Message("Someone new arrived!"));
}

void HostClient::handle() {
    this->acceptRemote();

    bool hasSocket = false;

    for(auto &remote : this->remotes) {
        if(remote == nullptr) continue;

        if(!remote->isConnected()) {
            this->messageCollection.push(new Message("Someone disconnected!"));
            delete remote;
            remote = nullptr;
            continue;
        }

        hasSocket = true;
        break;
    }

    if(!hasSocket) return;

    this->receive();

    fd_set fdread, fdwrite;

    int ret;

    FD_ZERO(&fdread);
    FD_ZERO(&fdwrite);

    for(auto remote : this->remotes) {
        if(remote == nullptr) continue;

        SOCKET socket = remote->getSocket();

        FD_SET(socket, &fdread);
        FD_SET(socket, &fdwrite);
    }

    ret = select(0, &fdread, &fdwrite, NULL, NULL);

    if(ret == SOCKET_ERROR) {
        this->messageCollection.push(new Message(std::format("Something went wrong with select(), error code -> {}", WSAGetLastError())));
        return;
    }

    if(ret <= 0) return;

    for(auto remote : this->remotes) {
        if(remote == nullptr) continue;

        SOCKET socket = remote->getSocket();

        if(FD_ISSET(socket, &fdread)) remote->handleReceive();
        if(FD_ISSET(socket, &fdwrite)) remote->handleSend();
    }
}