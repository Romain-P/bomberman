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
    } catch(std::exception const &e) {
        _client.release();
        return false;
    }
    _session = std::make_unique<GameSession>(_client.get());
    _handler.setSession(_session.get());
    return true;
}
