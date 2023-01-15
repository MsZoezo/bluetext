//
// Created by Zoezo on 1/15/2023.
//

#include "client.h"

Client::Client(MessageCollection* messageCollection) {
	this->messageCollection = messageCollection;

	WSADATA wsa;
	WORD version = MAKEWORD(2, 2);

	int result = WSAStartup(version, &wsa);

	if(result != 0) {
		this->messageCollection->push(new ErrorMessage(fmt::format("WSA Startup failed, Error code -> {}\nCodes can be found here -> https://learn.microsoft.com/en-us/windows/win32/winsock/windows-sockets-error-codes-2", result)));
		exit(1);
	}
}

Client::~Client() {
	WSACleanup();
}
