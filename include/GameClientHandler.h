//
// Created by romain on 01/06/18.
//

#ifndef CPP_INDIE_STUDIO_GAMECLIENTHANDLER_H
#define CPP_INDIE_STUDIO_GAMECLIENTHANDLER_H

#include <string>
#include "shared/INetworkClientHandler.h"
#include "GameServerController.h"

class GameServer;

class GameClientHandler: public INetworkClientHandler {
public:

    explicit GameClientHandler(GameServer *server) : INetworkClientHandler(), _server(), _controller(server){}

    void onConnect(NetworkClient *client) override;
    void onReceive(NetworkClient *client, char const *buffer, size_t length) override;
    void onSent(NetworkClient *client, char const *buffer, size_t length) override;
    void onDisconnect(NetworkClient *client) override;

private:

    GameServer *_server;
    GameServerController _controller;
};


#endif //CPP_INDIE_STUDIO_GAMECLIENTHANDLER_H
