//
// Created by romain on 01/06/18.
//

#ifndef CPP_INDIE_STUDIO_GAMESESSION_H
#define CPP_INDIE_STUDIO_GAMESESSION_H


#include <ANetworkClient.h>

class GameSession: public ANetworkClient {
public:
    GameSession(NetworkClient *client): ANetworkClient(client) {}

private:

};


#endif //CPP_INDIE_STUDIO_GAMESESSION_H
