//
// Created by Zoezo on 1/15/2023.
//

#ifndef BLUETEXT_HOSTCLIENT_H
#define BLUETEXT_HOSTCLIENT_H

#include "client.h"
#include <ws2bth.h>
#include <bluetoothapis.h>
#include <thread>
#include "../messages/systemMessage.h"

class HostClient : public Client {
private:
	SOCKET hostSocket;
	std::thread* acceptingThread;

	void acceptRemotes();

public:
	HostClient(MessageCollection* messageCollection);
	~HostClient();
};


#endif //BLUETEXT_HOSTCLIENT_H
