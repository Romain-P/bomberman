//
// Created by romain on 29/05/18.
//

#include <iostream>
#include "shared/NetworkClient.h"

void NetworkClient::init() {
    _buffer = std::move(_adapter->bufferFactory());
    _socket.init();
}

void NetworkClient::read() {
    size_t bytes = 0;
    char buffer[_adapter->readSize()];

    try {
        bytes = _socket.read(buffer, _adapter->readSize());
    } catch (std::exception &e) {
        std::cerr << "Client" << getId() << ": " << e.what() << std::endl;
        goto error;
    }

    if (bytes == 0) {
        error: close();
    } else
        _adapter->onDataReceived(this, buffer, bytes);
}

void NetworkClient::send(char *buffer, size_t length) {
    _socket.send(buffer, length);
}

void NetworkClient::close(bool force) {
    _closed = true;

    if (force)
        _socket.close();
}

ANetworkClientAdapter *NetworkClient::getAdapter() {
    return _adapter;
}

ANetworkBuffer *NetworkClient::getBuffer() {
    return _buffer.get();
}

socket_fd_t NetworkClient::getId() const {
    return _socket.getId();
}
