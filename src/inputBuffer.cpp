//
// Created by Zoezo on 1/15/2023.
//

#include "inputBuffer.h"

std::string InputBuffer::retrieve(short maxLength) const {
	if(this->buffer.length() < maxLength) return this->buffer;
	return this->buffer.substr(this->buffer.length() - maxLength, maxLength);
}

void InputBuffer::add(char character) {
	this->buffer.push_back(character);

	this->translateCodes();
}

void InputBuffer::pop() {
	if(this->buffer.length() == 0) return;

	this->buffer.pop_back();
}

void InputBuffer::clear() {
	this->buffer.clear();
}

void InputBuffer::translateCodes() {
	std::string newBuffer = this->buffer;

	for(const auto&[regex, emoji] : codes) {
		newBuffer = std::regex_replace(newBuffer, regex, emoji);
	}

	this->buffer = newBuffer;
}

int InputBuffer::length() {
	return this->buffer.length();
}
