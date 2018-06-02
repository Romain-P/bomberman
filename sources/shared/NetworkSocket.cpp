//
// Created by romain on 29/05/18.
//

#include <stdexcept>
#include <arpa/inet.h>
#include "shared/NetworkSocket.h"

void NetworkSocket::init() {
    switch (_mode) {
        case ACTIVE:
            create(false);
            break;
        case PASSIVE:
            create(true);
            break;
        case CHILD:
            accept();
            break;
        default:
            throw std::runtime_error("Socket::init(): invalid mode");
    }
}

void NetworkSocket::create(bool listen) {
    if ((_id = socket(AF_INET, SOCK_STREAM, 0)) == ERROR)
        goto error;

    insocket_t server;
    server.sin_addr.s_addr = inet_addr(_ip.c_str());
    server.sin_family = AF_INET;
    server.sin_port = htons(_port);

    if (!listen && ::connect(_id, reinterpret_cast<socket_t *>(&server), sizeof(server)) == ERROR)
        perror("connect");
    else if (listen && (bind(_id, (socket_t *) &server, sizeof(server)) == ERROR || ::listen(_id, SOMAXCONN) == ERROR))
        perror("listen & bind");
    else {
        if (_port == RANDOM_PORT) {
            socklen_t len = sizeof(server);
            getsockname(_id, reinterpret_cast<socket_t *>(&server), &len);

            _port = static_cast<uint16_t >(ntohs(server.sin_port));
        }
        return;
    }

    error:
    throw std::runtime_error("NetworkSocket::create(): can't create the socket");
}

void NetworkSocket::accept() {
    insocket_t socket;
    socklen_t size = sizeof(socket);

    _id = ::accept(_server_fd, reinterpret_cast<socket_t *>(&socket), &size);

    if (_id == ERROR) {
        perror("accept");
        throw std::runtime_error("NetworkSocket::accept(): can't create the socket");
    }

    char retrieved[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &socket.sin_addr, retrieved, INET_ADDRSTRLEN);
    _ip = std::string(retrieved);
}

void NetworkSocket::send(void *buffer, size_t length) {
    if (::send(_id, buffer, length, 0) != ERROR) return;

    perror("send");
    throw std::runtime_error("NetworkSocket::send: impossible to send data");
}

size_t NetworkSocket::read(void *buffer, size_t length) {
    ssize_t bytes = ::recv(_id, buffer, length, 0);

    if (bytes != ERROR)
        return (size_t) bytes;

    perror("read");
    throw std::runtime_error("NetworkSocket::read: impossible to read data");
}

std::string const &NetworkSocket::getIpAddress() const {
    return _ip;
}

uint16_t NetworkSocket::getPort() const {
    return _port;
}

NetworkSocket::Mode NetworkSocket::getMode() const {
    return _mode;
}

bool NetworkSocket::isClosed() const {
    return _closed;
}

socket_fd_t NetworkSocket::getId() const {
    return _id;
}

void NetworkSocket::close() {
    if (_closed) return;

    ::close(_id);
    _closed = true;
}
