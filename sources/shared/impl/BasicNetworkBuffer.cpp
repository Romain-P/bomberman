//
// Created by romain on 30/05/18.
//

#include <cstring>
#include "shared/BasicNetworkBuffer.h"

bool BasicNetworkBuffer::append(char *bytes, size_t length) {
    size_t nextPosition = _position + length;

    if (nextPosition + 1 > _maxSize)
        return false;
    else if (nextPosition + 1 > _bytes.size())
        _bytes.resize(nextPosition + 1);

    memcpy(&_bytes[_position + 1], bytes, length);
    _position += length;
    return true;
}

void BasicNetworkBuffer::clear() {
    _bytes.clear();
    _position = -1;
}

char *BasicNetworkBuffer::getBytes() {
    return &_bytes[0];
}

void BasicNetworkBuffer::allocate(size_t nbytes) {
    _bytes.resize(_bytes.size() + nbytes);
}

void BasicNetworkBuffer::resize(size_t nbytes) {
    _bytes.resize(nbytes);
}

bool BasicNetworkBuffer::drop(size_t from, size_t to) {
    size_t size = _bytes.size();

    if (from > size || to > size)
        return false;

    auto start = _bytes.begin() + from;
    _bytes.erase(start, start + to);
}
