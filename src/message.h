
#ifndef BLUETEXT_MESSAGE_H
#define BLUETEXT_MESSAGE_H

#include <string>

class Message {
private:
    std::string content;

public:
    Message(std::string content);
    const std::string& getContent() const;

    int getLength();
};


#endif //BLUETEXT_MESSAGE_H
