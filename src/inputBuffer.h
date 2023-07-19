
#ifndef BLUETEXT_INPUTBUFFER_H
#define BLUETEXT_INPUTBUFFER_H

#include <string>

class InputBuffer {
private:
    char* buffer;
    int maxLength, length;

public:
    InputBuffer(int maxLength);
    ~InputBuffer();

    void add(char character);
    void remove();

    void clear();

    int getLength();
    int getMaxLength();

    std::string& retrieve(int maxLength = 0);
};


#endif //BLUETEXT_INPUTBUFFER_H
