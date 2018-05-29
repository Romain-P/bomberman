//
// Created by romain on 29/05/18.
//

#ifndef CPP_INDIE_STUDIO_INETWORKCLIENTBUFFER_H
#define CPP_INDIE_STUDIO_INETWORKCLIENTBUFFER_H

#include <sys/types.h>

class ANetworkBuffer {
public:

    ANetworkBuffer(size_t maxSize) : _position(-1), _maxSize(maxSize) {};
    virtual ~ANetworkBuffer() = default;

    virtual void append(char *bytes, size_t length) = 0;
    virtual void clear() = 0;
    virtual void *getBytes() = 0;
    virtual void allocate(size_t nbytes) = 0;

    ssize_t getPosition() const;
    void setPosition(size_t position);
    size_t getMaxSize() const;

protected:

    ssize_t _position;
    size_t _maxSize;
};


#endif //CPP_INDIE_STUDIO_INETWORKCLIENTBUFFER_H
