//
// Created by romain on 29/05/18.
//

#include "shared/ANetworkBuffer.h"

size_t ANetworkBuffer::getPosition() const {
    return _position;
}

void ANetworkBuffer::setPosition(size_t position) {
    _position = position;
}

size_t ANetworkBuffer::getMaxSize() const {
    return _maxSize;
}

bool ANetworkBuffer::empty() {
    return _position == 0;
}
