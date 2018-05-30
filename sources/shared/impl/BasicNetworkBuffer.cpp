//
// Created by romain on 30/05/18.
//

#include <cstring>
#include "shared/BasicNetworkBuffer.h"

bool BasicNetworkBuffer::append(char *bytes, size_t length) {
    size_t newLength = _bytes.size() + length;

    if (newLength > _maxSize)
        return false;

    _bytes.resize(newLength);
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
