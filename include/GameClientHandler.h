//
// Created by romain on 01/06/18.
//

#ifndef CPP_INDIE_STUDIO_NNETWORKCLIENTHANDLER_H
#define CPP_INDIE_STUDIO_NNETWORKCLIENTHANDLER_H

#include <string>
#include "shared/INetworkClientHandler.h"
#include "GameServerController.h"
#include "GameServer.h"

class GameClientHandler: public INetworkClientHandler {
public:

    explicit GameClientHandler(GameServer *server) : _server(), _controller(server), INetworkClientHandler() {}

    void onConnect(NetworkClient *client) override;
    void onReceive(NetworkClient *client, char const *buffer, size_t length) override;
    void onSent(NetworkClient *client, char const *buffer, size_t length) override;
    void onDisconnect(NetworkClient *client) override;

private:

    GameServer *_server;
    GameServerController _controller;
};


#endif //CPP_INDIE_STUDIO_NETWORKCLIENTHANDLER_H
