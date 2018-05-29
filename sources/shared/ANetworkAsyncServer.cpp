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
    if (socket == _socket.getId()) {
        auto newClient = std::make_unique<NetworkClient>(socket, _adapter.get());

        newClient->init();
        addListened(newClient->getId());
        _clients[newClient->getId()] = std::move(newClient);
        _adapter->getHandler()->onConnect(newClient.get());
    } else
        _clients[socket]->read();
}

void NetworkAsyncServer::onListenerClosed(bool interrupted) {
    for (auto &keyset: _clients) {
        auto client = keyset.second.get();

        _adapter->getHandler()->onDisconnect(client);

        delListened(client->getId());
        client->close();
    }
    _clients.clear();
}

socket_fd_t NetworkAsyncServer::defineServerFd() {
    return _socket.getId();
}

clients_t &NetworkAsyncServer::getClients() {
    return _clients;
}
