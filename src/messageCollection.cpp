
#include "messageCollection.h"

Message *MessageCollection::operator[](int index) {
    return this->messages.at(index);
}

void MessageCollection::push(Message *message) {
    this->messages.push_back(message);

    this->collectionChanged = true;
}

int MessageCollection::size() {
    return this->messages.size();
}

bool MessageCollection::hasChanged() {
    if(!this->collectionChanged) return false;

    this->collectionChanged = false;
    return true;
}

