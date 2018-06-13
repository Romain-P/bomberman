//
// Created by romain on 02/06/18.
//

#include "GameSessionConnector.h"

GameSession *GameSessionConnector::getSession() {
    return _session.get();
}

bool GameSessionConnector::tryConnect(std::string const &ip, uint16_t gamePort) {
    _client = std::make_unique<NetworkClient>(ip, gamePort, &_adapter);
    try {
        _client->init();
    } catch(...) {
        _client.release();
        return false;
    }
    _session = std::make_unique<GameSession>(_client.get());
    _handler.setSession(_session.get());
    NetworkAsyncListener::start();
    return true;
}

void GameSessionConnector::onSocketNotified(socket_fd_t socket_id) {
    _client->read();

    if (_client->isClosed())
        NetworkAsyncListener::close();
}

void GameSessionConnector::onListenerClosed(bool interrupted) {
    //_client already closed by parent class
    _handler.onDisconnect(_client.get());
}

socket_fd_t GameSessionConnector::defineServerFd() {
    return _client->getId();
}

void GameSessionConnector::closeConnection() {
    NetworkAsyncListener::close();
}

void GameSessionConnector::pollEvent() {
    _handler.getController().poll();
}
