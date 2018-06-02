//
// Created by romain on 02/06/18.
//

#ifndef CPP_INDIE_STUDIO_GAMESESSIONCONTROLLER_H
#define CPP_INDIE_STUDIO_GAMESESSIONCONTROLLER_H


#include "ANetworkController.h"
#include "GameSession.h"
#include "HelloConnectMessage.h"

class GameSessionController: public ANetworkController {
public:

    GameSessionController() : ANetworkController() {}

    void defineMessageHandlers(handlers_t &handlers) override;

    void onConnect(GameSession *session, HelloConnectMessage *msg);
    void onDisconnect(GameSession *session);

private:

};


#endif //CPP_INDIE_STUDIO_GAMESESSIONCONTROLLER_H
