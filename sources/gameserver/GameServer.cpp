//
// Created by romain on 02/06/18.
//

#include <GameClientHandler.h>
#include <NetworkClientAdapter.h>
#include "GameServer.h"

std::unique_ptr<ANetworkClientAdapter> GameServer::defineClientAdapter() {
    return std::make_unique<NetworkClientAdapter>(1024, &_handler);
}

GameClient *GameServer::findClient(size_t clientId) {
    for (auto &keyset: _clients) {
        auto &client = keyset.second;

        if (client->getId() == clientId)
            return client.get();
    }
    return nullptr;
}

game_clients_t &GameServer::getClients() {
    return _clients;
}

void GameServer::onServerClosed() {
    //TODO: you can do anything before that all clients are closed.
}

size_t &GameServer::getMaxPlayers() {
    return _maxPlayers;
}

bool &GameServer::started() {
    return _started;
}
