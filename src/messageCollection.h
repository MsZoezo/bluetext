
#ifndef BLUETEXT_MESSAGECOLLECTION_H
#define BLUETEXT_MESSAGECOLLECTION_H


#include <vector>
#include <optional>
#include "message.h"

class MessageCollection {
private:
    std::vector<Message*> messages;

    bool collectionChanged = false;

public:
    Message* operator[](int index);

    void push(Message* message);
    int size();

    bool hasChanged();

    void clear();
};


#endif //BLUETEXT_MESSAGECOLLECTION_H
