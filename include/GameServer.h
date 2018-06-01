//
// Created by romain on 01/06/18.
//

#ifndef CPP_INDIE_STUDIO_GAMESERVER_H
#define CPP_INDIE_STUDIO_GAMESERVER_H


#include <unordered_map>
#include <GameClient.h>

using clients_t = std::unordered_map<size_t, std::unique_ptr<GameClient>>;

class GameServer {
public:

    GameServer() : _clients() {}

    clients_t &getClients();
    void shutdown();

private:

    clients_t _clients;
};


#endif //CPP_INDIE_STUDIO_GAMESERVER_H
