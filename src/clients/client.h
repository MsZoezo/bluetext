//
// Created by Zoezo on 1/15/2023.
//

#ifndef BLUETEXT_CLIENT_H
#define BLUETEXT_CLIENT_H

#include <WinSock2.h>
#include "../messages/messageCollection.h"
#include "../messages/errorMessage.h"

class Client {
protected:
	MessageCollection* messageCollection;

public:
	Client(MessageCollection* messageCollection);
	~Client();
};

#endif //BLUETEXT_CLIENT_H
