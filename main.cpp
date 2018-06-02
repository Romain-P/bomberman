
#include <iostream>
#include "BomberWave.hpp"
#include <memory>
#include "GameServer.h"
#include "GameSessionConnector.h"
#include <thread>

void launchServer(GameServer *server) {
    server->start();
}

void networkExample()
{
    GameServer server("127.0.0.1", RANDOM_PORT);
    std::thread thread(launchServer, &server);

    //wait for server initialisation
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    GameSessionConnector connector;
    connector.tryConnect("127.0.0.1", server.getPort());

    //server.close();
    thread.join();
}

int main() {
    try {
        BomberWave game;
        game.Launch();
    }
    catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
        return 84;
    }
}