//
// Created by romain on 29/05/18.
//

#include <iostream>
#include "shared/ANetworkAsyncServer.h"

void ANetworkAsyncServer::start() {
    _socket.init();
    _adapter = std::move(defineClientAdapter());

    NetworkAsyncListener::start();
}

void ANetworkAsyncServer::close() {
    NetworkAsyncListener::close();
}

void ANetworkAsyncServer::onSocketNotified(socket_fd_t socket) {
    NetworkClient *client;

    if (socket == _socket.getId()) {
        auto newClient = std::make_unique<NetworkClient>(socket, _adapter.get());

        client = newClient.get();
        addListened(client->getId());
        _clients[client->getId()] = std::move(newClient);
        client->init();
    } else {
        client = _clients[socket].get();
        client->read();
    }
    if (client->isClosed()) {
        delListened(client->getId());
        client->close(true);
    }
}

void ANetworkAsyncServer::onListenerClosed(bool interrupted) {
    for (auto &keyset: _clients) {
        auto client = keyset.second.get();
        delListened(client->getId());
        client->close(true);
    }
    _clients.clear();
}

socket_fd_t ANetworkAsyncServer::defineServerFd() {
    return _socket.getId();
}
