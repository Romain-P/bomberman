//
// Created by romain on 01/06/18.
//

#include <iostream>
#include <sstream>
#include "NetworkMessage.h"
#include "NetworkProtocol.h"
#include "GameClientHandler.h"
#include "shared/NetworkClient.h"
#include "GameServer.h"

void GameClientHandler::onConnect(NetworkClient *client) {
    log("[Server] new client %d\n", client->getId());
    _server->getClients()[client->getId()] = std::make_unique<GameClient>(client);
    _controller.onConnect(_server->getClients()[client->getId()].get());
}

void GameClientHandler::onReceive(NetworkClient *client, char const *buffer, size_t length) {
    GameClient *player = _server->findClient(client->getId());

    if (!player) return;

    auto msg = player->receive(buffer, length);

    std::ostringstream s;
    s << *msg;
    log("[Server] recv\t\t\t<--\t\t[Client %d]:\t\t%s\n", client->getId(), s.str().c_str());

    _controller.parseMessage(player, msg.get());
}

void GameClientHandler::onSent(NetworkClient *client, char const *buffer, size_t length) {
    GameClient *player = _server->findClient(client->getId());

    if (!player) return;

    buffer += NetworkProtocol::HEADER_INT_BYTES;
    length -= NetworkProtocol::HEADER_INT_BYTES;

    auto msg = player->receive(buffer, length);

    std::ostringstream s;
    s << *msg;
    log("[Server] sent\t\t\t-->\t\t[Client %d]:\t\t%s\n", client->getId(), s.str().c_str());
}

void GameClientHandler::onDisconnect(NetworkClient *client) {
    GameClient *player = _server->findClient(client->getId());

    if (!player) return;

    _controller.onDisconnect(player);
    log("[Server] del client %d\n", client->getId());
}