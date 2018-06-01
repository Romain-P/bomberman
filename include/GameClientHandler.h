//
// Created by romain on 01/06/18.
//

#ifndef CPP_INDIE_STUDIO_NNETWORKCLIENTHANDLER_H
#define CPP_INDIE_STUDIO_NNETWORKCLIENTHANDLER_H

#include <string>
#include "shared/INetworkClientHandler.h"
#include "GameServer.h"
#include "GameController.h"

class GameClientHandler: public INetworkClientHandler {
public:

    explicit GameClientHandler(GameServer *server) : _controller(server), INetworkClientHandler() {}

    void onConnect(NetworkClient *client) override;
    void onReceive(NetworkClient *client, char const *buffer, size_t length) override;
    void onSent(NetworkClient *client, char const *buffer, size_t length) override;
    void onDisconnect(NetworkClient *client) override;

private:

    GameServer *_server;
    GameController _controller;

    GameClient *find(NetworkClient *client);
};


#endif //CPP_INDIE_STUDIO_NETWORKCLIENTHANDLER_H
