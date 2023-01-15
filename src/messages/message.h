//
// Created by Zoezo on 1/15/2023.
//

#ifndef BLUETEXT_MESSAGE_H
#define BLUETEXT_MESSAGE_H

#include <string>

class Message {
protected:
	std::string text;
	int length;

public:
	std::string getText() const;
	int getLength() const;
};


#endif //BLUETEXT_MESSAGE_H
