//
// Created by romain on 01/06/18.
//

#include <iostream>
#include <RequestStartGameMessage.h>
#include <LobbyUpdateMessage.h>
#include <GameDataMessage.h>
#include <GameMapFactory.h>
#include "HelloConnectMessage.h"
#include "GameServerController.h"
#include "GameServer.h"
#include "InputMessage.h"

void GameServerController::defineMessageHandlers(handlers_t &handlers) {
    handlers[RequestStartGameMessage::PROTOCOL_ID] = handler(*this, &GameServerController::onStartRequested);
    handlers[RequestLobbyMessage::PROTOCOL_ID] = handler(*this, &GameServerController::onJoinAsked);
    handlers[InputMessage::PROTOCOL_ID] = handler(*this, &GameServerController::onInputReceived);
}

void GameServerController::onConnect(GameClient *client) {
    client->send(HelloConnectMessage());
}

void GameServerController::onDisconnect(GameClient *client) {

}

void GameServerController::onStartRequested(GameClient *client, RequestStartGameMessage *msg) {
    size_t players = _server->getClients().size();

    if (players == 1 || _server->started()) return;

    GameDataSerializer serializer;
    GameMapFactory factory(serializer);

    auto map = factory.generate(players); //TODO: generate dynamic map / factory.generate(nbPlayers)
    std::vector<GameDataMessage::PlayerInformation> infos;

    for (size_t i = 0; i < players; ++i) {
        auto &spawn = map->getPlayerSpawns().at(i);

        infos.push_back({_server->getClients().at(i)->getId(), spawn.X, spawn.Y});
    }

    for (auto &keyset: _server->getClients()) {
        GameClient *player = keyset.second.get();

        player->send(GameDataMessage(*map, infos));
    }
    _server->started() = true;
}

void GameServerController::onJoinAsked(GameClient *client, RequestLobbyMessage *msg) {
    size_t readyPlayers = _server->getClients().size();
    size_t maxPlayers = _server->getMaxPlayers();

    if (readyPlayers >= _server->getMaxPlayers() || _server->started())
        client->kick();
    else
        client->send(LobbyUpdateMessage(readyPlayers, maxPlayers));
}

void GameServerController::onInputReceived(GameClient *client, InputMessage *msg) {
    for (auto &keyset: _server->getClients()) {
        auto &player = keyset.second;

        if (player->getId() == client->getId()) continue;

        client->send(InputMessage(msg->getType(), client->getId()));
    }
}
