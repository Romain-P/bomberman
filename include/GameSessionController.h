//
// Created by romain on 02/06/18.
//

#ifndef CPP_INDIE_STUDIO_GAMESESSIONCONTROLLER_H
#define CPP_INDIE_STUDIO_GAMESESSIONCONTROLLER_H

class GameSessionController;
#include <thread>
#include <deque>
#include "ANetworkController.h"
#include "GameSession.h"
#include "HelloConnectMessage.h"
#include "LobbyUpdateMessage.h"
#include "GameDataMessage.h"
#include "InputMessage.h"
#include "GameLobby.hpp"
#include "GameManager.hpp"
#include "GameClient.h"

class GameSessionController: public ANetworkController {
public:

    GameSessionController() : ANetworkController(), _state(ON_WAIT) {}

    struct Waiting {
        GameSession *client;
        std::unique_ptr<NetworkMessage> msg;
    };
    enum State {
        ON_WAIT,
        ON_LOBBY,
        ON_GAME
    };
    void defineMessageHandlers(handlers_t &handlers) override;
    void poll();
    void add(GameSession *client, std::unique_ptr<NetworkMessage> &msg);
    std::unique_ptr<GameLobby> &getlobby() { return _lobby;}
    std::unique_ptr<NetworkGameManager> &getGameManager() { return _manager;}
    void onConnect(GameSession *session, HelloConnectMessage *msg);
    void onDisconnect(GameSession *session);
    void onLobbyUpdated(GameSession *session, LobbyUpdateMessage *msg);
    void loadGameData(GameSession *session, GameDataMessage *msg);
    void onInputReceived(GameSession *session, InputMessage *msg);
    State &getState();
private:
    State _state;
    std::mutex _locker;
    std::deque<Waiting> _waiting;
    std::unique_ptr<GameLobby> _lobby;
    std::unique_ptr<NetworkGameManager> _manager;
};


#endif //CPP_INDIE_STUDIO_GAMESESSIONCONTROLLER_H
