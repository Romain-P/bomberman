//
// Created by romain on 01/06/18.
//

#ifndef CPP_INDIE_STUDIO_GAMECLIENT_H
#define CPP_INDIE_STUDIO_GAMECLIENT_H


#include <shared/NetworkClient.h>
#include <NetworkMessage.h>
#include "ANetworkClient.h"

class GameClient: public ANetworkClient {
public:

    explicit GameClient(NetworkClient *client) : ANetworkClient(client) {}

private:

    //TODO: game player vars
};


#endif //CPP_INDIE_STUDIO_GAMECLIENT_H