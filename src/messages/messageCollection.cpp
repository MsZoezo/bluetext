//
// Created by Zoezo on 1/15/2023.
//

#include "messageCollection.h"

MessageCollection::~MessageCollection() {
	for(Message* message : this->messages) {
		delete message;
	}

	this->messages.clear();
}

Message* MessageCollection::operator[](int index) {
	return this->messages[index];
}

void MessageCollection::push(Message* message) {
	this->messages.push_back(message);
}

int MessageCollection::size() {
	return this->messages.size();
}
