//
// Created by romain on 30/05/18.
//

#include <cstring>
#include "shared/BasicNetworkBuffer.h"

bool BasicNetworkBuffer::append(char const *bytes, size_t length) {
    size_t position = _position + length;

    if (position > _maxSize)
        return false;
    else if (position > _bytes.size())
        _bytes.resize(position);

    memcpy(&_bytes[_position], bytes, length);
    _position += length;
    return true;
}

void BasicNetworkBuffer::clear() {
    _bytes.clear();
    _position = 0;
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

size_t BasicNetworkBuffer::getSize() const {
    return _bytes.size();
}
