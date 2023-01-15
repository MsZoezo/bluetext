//
// Created by Zoezo on 1/15/2023.
//

#include "hostClient.h"

HostClient::HostClient(MessageCollection *messageCollection) : Client(messageCollection) {
	int family = AF_BTH;
	int type = SOCK_STREAM;
	int protocol = BTHPROTO_RFCOMM;

	SOCKET hostSocket = socket(family, type, protocol);

	if(hostSocket == INVALID_SOCKET) {
		this->messageCollection->push(new ErrorMessage(fmt::format("Initializing host socket failed. Error code -> {}", WSAGetLastError())));
		exit(1);
	}

	this->hostSocket = hostSocket;

	SOCKADDR_BTH hint;
	int size = sizeof hint;
	memset(&hint, 0, size);
	hint.addressFamily = AF_BTH;
	hint.port = 25;
	hint.serviceClassId = RFCOMM_PROTOCOL_UUID;

	if(bind(hostSocket, (sockaddr*) &hint, size) == SOCKET_ERROR) {
		this->messageCollection->push(new ErrorMessage(fmt::format( "Failed to bind host socket. Error code -> {}", WSAGetLastError())));
		exit(1);
	}

	if(listen(hostSocket, SOMAXCONN) == SOCKET_ERROR) {
		this->messageCollection->push(new ErrorMessage(fmt::format("Failed to listen on host socket. Error code -> {}", WSAGetLastError())));
		exit(1);
	}

	if(getsockname(hostSocket, (sockaddr*) &hint, &size) == SOCKET_ERROR) {
		this->messageCollection->push(new ErrorMessage(fmt::format("Failed to retrieve address. Error code -> {}", WSAGetLastError())));
		exit(1);
	}

	this->ip = hint.btAddr;

	GUID mServiceGuid = {0x00001101, 0x0000, 0x1000, 0x66, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB}; // Can be anything

	WSAQUERYSET wsaQuery = {0};
	wsaQuery.dwSize = sizeof(WSAQUERYSET);
	wsaQuery.lpszServiceInstanceName = (LPSTR) L"BT Service"; // Can be anything
	wsaQuery.lpszComment = (LPSTR) L"bt"; //Can be anything
	wsaQuery.lpServiceClassId = &mServiceGuid;
	wsaQuery.dwNameSpace = NS_BTH;
	wsaQuery.dwNumberOfCsAddrs = 1;

	CSADDR_INFO addrInfo = {0};
	addrInfo.LocalAddr.lpSockaddr = (sockaddr*) &hint;
	addrInfo.LocalAddr.iSockaddrLength = size;
	addrInfo.iSocketType = SOCK_STREAM;
	addrInfo.iProtocol = BTHPROTO_RFCOMM;

	wsaQuery.lpcsaBuffer = &addrInfo;
	WSASetService(&wsaQuery, RNRSERVICE_REGISTER, 0);

	std::thread thread(&HostClient::acceptRemotes, this);
	thread.detach();
}

void HostClient::acceptRemotes() {
	SOCKET acceptSocket = accept(this->hostSocket, NULL, 0);

	this->messageCollection->push(new SystemMessage("User connected!"));
}

