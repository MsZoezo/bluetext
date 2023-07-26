
#ifndef BLUETEXT_INPUTBUFFER_H
#define BLUETEXT_INPUTBUFFER_H

#include <string>

class InputBuffer {
private:
    char* buffer;
    int maxLength, length;

public:
    InputBuffer(int maxLength);

    InputBuffer();

    ~InputBuffer();

    void add(char character);
    void remove();
    void removeWord();

    void clear();

    int getLength() const;
    int getMaxLength() const;

    std::string & retrieve(int maxLength = 0) const;
};


#endif //BLUETEXT_INPUTBUFFER_H
