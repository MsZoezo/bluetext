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
	this->collectionChanged = true;
}

int MessageCollection::size() {
	return this->messages.size();
}

Message* MessageCollection::at(int index) {
	return this->messages[index];
}

bool MessageCollection::hasChanged() {
	if(this->collectionChanged) {
		this->collectionChanged = false;
		return true;
	}
	return false;
}
