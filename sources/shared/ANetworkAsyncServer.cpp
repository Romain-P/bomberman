//
// Created by romain on 29/05/18.
//

#include <iostream>
#include "shared/ANetworkAsyncServer.h"

void NetworkAsyncServer::start() {
    _socket.init();
    _adapter = std::move(defineClientAdapter());

    NetworkAsyncListener::start();
}

void NetworkAsyncServer::close() {
    NetworkAsyncListener::close();
}

void NetworkAsyncServer::onSocketNotified(socket_fd_t socket) {
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

void NetworkAsyncServer::onListenerClosed(bool interrupted) {
    for (auto &keyset: _clients) {
        auto client = keyset.second.get();
        delListened(client->getId());
        client->close(true);
    }
    _clients.clear();
}

socket_fd_t NetworkAsyncServer::defineServerFd() {
    return _socket.getId();
}

clients_t &NetworkAsyncServer::getClients() {
    return _clients;
}
