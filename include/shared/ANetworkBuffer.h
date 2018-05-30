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

    /**
     * Should Append to the buffer the given bytes
     *
     * @param bytes     bytes to push at the end of the buffer
     * @param length    n bytes to add
     * @return          true if the buffer size lower than the buffer max size, false otherwise
     */
    virtual bool append(char *bytes, size_t length) = 0;
    virtual void clear() = 0;
    virtual char *getBytes() = 0;

    ssize_t getPosition() const;
    size_t getSize() const;
    void setPosition(size_t position);
    size_t getMaxSize() const;

protected:

    ssize_t _position;
    size_t _maxSize;
};


#endif //CPP_INDIE_STUDIO_INETWORKCLIENTBUFFER_H
