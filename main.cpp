
#include <iostream>
#include <memory>
#include <GameServer.h>

int main()
{
    GameServer server("127.0.0.1", RANDOM_PORT);
    server.start();
    return 0;
}