
#include <iostream>
#include <memory>
#include "GameServer.h"
#include "GameSessionConnector.h"
#include <thread>

void launchServer(GameServer *server) {
    server->start();
}

int main()
{
    GameServer server("127.0.0.1", RANDOM_PORT);
    std::thread thread(launchServer, &server);

    //wait for server initialisation
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    GameSessionConnector connector;
    connector.tryConnect("127.0.0.1", server.getPort());

    //server.close();
    thread.join();
    return 0;
}