//
// Created by romain on 01/06/18.
//

#include "GameServer.h"

void GameServer::shutdown() {
    for (auto &keyset: _clients) {
        auto &client = keyset.second;
        client->kick(true);
    }
}

clients_t &GameServer::getClients() {
    return _clients;
}
