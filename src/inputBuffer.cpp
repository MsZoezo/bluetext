
#include "inputBuffer.h"

InputBuffer::InputBuffer(int maxLength) : maxLength{maxLength} {
    this->buffer = new char[maxLength];
    this->length = 0;
}

InputBuffer::~InputBuffer() {
    delete[] this->buffer;
}

std::string& InputBuffer::retrieve(int maxLength) {
    // Should check if the size is 0 and throw if it is.
    int offset = 0;
    int length = this->length;

    if(maxLength != 0 && this->length > maxLength) {
        offset = this->length - maxLength;
        length = maxLength;
    }

    return *(new std::string(this->buffer + offset, length));
}

int InputBuffer::getLength() {
    return this->length;
}

int InputBuffer::getMaxLength() {
    return this->maxLength;
}

void InputBuffer::add(char character) {
    if(this->length == this->maxLength) return;

    this->buffer[this->length] = character;
    this->length++;
}

void InputBuffer::remove() {
    if(this->length == 0) return;
    this->length--;
}

void InputBuffer::clear() {
    this->length = 0;
}