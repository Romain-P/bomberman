//
// Created by romain on 01/06/18.
//

#include <iostream>
#include "NetworkMessage.h"
#include "NetworkProtocol.h"
#include "GameClientHandler.h"
#include "shared/NetworkClient.h"

void GameClientHandler::onConnect(NetworkClient *client) {
    auto player = std::make_unique<GameClient>(client);

    _server->getClients()[client->getId()] = std::move(player);
    _controller.onConnect(player.get());
}

void GameClientHandler::onReceive(NetworkClient *client, char const *buffer, size_t length) {
    GameClient *player = find(client);

    if (!player) return;

    auto msg = player->receive(buffer, length);
    std::cerr << "[Server] received\t<--\t\t[Client " << client->getId() << "]:\t\t" << msg.get() << std::endl;

    _controller.parseMessage(player, msg.get());
}

void GameClientHandler::onSent(NetworkClient *client, char const *buffer, size_t length) {
    GameClient *player = find(client);

    if (!player) return;

    auto msg = player->receive(buffer, length);
    std::cerr << "[Server] sent\t-->\t\t[Client " << client->getId() << "]:\t\t" << msg.get() << std::endl;
}

void GameClientHandler::onDisconnect(NetworkClient *client) {
    GameClient *player = find(client);

    if (!player) return;

    _controller.onDisconnect(player);
}

GameClient *GameClientHandler::find(NetworkClient *client) {
    for (auto &keyset: _server->getClients()) {
        auto &gameClient = keyset.second;

        if (gameClient->getId() == client->getId())
            return gameClient.get();
    }
    client->close();
    return nullptr;
}
