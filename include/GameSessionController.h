//
// Created by romain on 02/06/18.
//

#ifndef CPP_INDIE_STUDIO_GAMESESSIONCONTROLLER_H
#define CPP_INDIE_STUDIO_GAMESESSIONCONTROLLER_H


#include "ANetworkController.h"
#include "GameSession.h"
#include "HelloConnectMessage.h"
#include "LobbyUpdateMessage.h"
#include "GameDataMessage.h"
#include "InputMessage.h"
#include "GameManager.hpp"
#include "GameLobby.hpp"

class GameSessionController: public ANetworkController {
public:

    GameSessionController() : ANetworkController() {}

    void defineMessageHandlers(handlers_t &handlers) override;

    void onConnect(GameSession *session, HelloConnectMessage *msg);
    void onDisconnect(GameSession *session);

    void onLobbyUpdated(GameSession *session, LobbyUpdateMessage *msg);
    void loadGameData(GameSession *session, GameDataMessage *msg);
    void onInputReceived(GameSession *session, InputMessage *msg);

private:
    GameLobby _lobby;
    NetworkGameManager _manager;
};


#endif //CPP_INDIE_STUDIO_GAMESESSIONCONTROLLER_H
