//
// Created by Zoezo on 1/15/2023.
//

#ifndef BLUETEXT_MESSAGECOLLECTION_H
#define BLUETEXT_MESSAGECOLLECTION_H

#include "message.h"
#include <vector>

class MessageCollection {
private:
	std::vector<Message*> messages;
	bool collectionChanged = false;

public:
	~MessageCollection();

	Message* operator[](int index);
	void push(Message* message);
	int size();
	bool hasChanged();

	Message* at(int index);
};


#endif //BLUETEXT_MESSAGECOLLECTION_H
