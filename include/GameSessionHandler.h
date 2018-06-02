//
// Created by romain on 02/06/18.
//

#ifndef CPP_INDIE_STUDIO_GAMESESSIONHANDLER_H
#define CPP_INDIE_STUDIO_GAMESESSIONHANDLER_H


#include <shared/NetworkClient.h>
#include "GameSession.h"
#include "GameSessionController.h"

class GameSessionHandler: public INetworkClientHandler {
public:
    explicit GameSessionHandler() : INetworkClientHandler(), _session(), _controller() {
        _controller.init();
    }

    void onConnect(NetworkClient *client) override;
    void onReceive(NetworkClient *client, char const *buffer, size_t length) override;
    void onSent(NetworkClient *client, char const *buffer, size_t length) override;
    void onDisconnect(NetworkClient *client) override;

    void setSession(GameSession *session);

private:
    GameSession *_session;
    GameSessionController _controller;
};


#endif //CPP_INDIE_STUDIO_GAMESESSIONHANDLER_H
