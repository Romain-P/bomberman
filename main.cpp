
#include <iostream>
#include "BomberWave.hpp"
#include <memory>
#include "GameServer.h"
#include "GameSessionConnector.h"
#include "sources/GameObjects/Test.h"
#include <thread>
#include <GameDataSerializer.h>
#include <GameMapFactory.h>
#include <driverChoice.h>
#include <Exceptions.hpp>

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows" /ENTRY:mainCRTStartup)
#endif

irrklang::ISoundEngine *SoundEngine = irrklang::createIrrKlangDevice();

irr::IrrlichtDevice *InitDevice()
{
    irr::IrrlichtDevice *device;
    irr::video::E_DRIVER_TYPE driverType = irr::driverChoiceConsole();
    if (driverType == irr::video::EDT_COUNT)
        throw(InitialisationException("Error : Driver could not be loaded"));
    device = irr::createDevice(driverType,
                               irr::core::dimension2d<irr::u32>(1920, 1080), 16, false, false, false, nullptr);
    if (device == nullptr)
        throw(InitialisationException("Error : Device creation failed"));
    device->setWindowCaption(L"BomberWave");
    return device;
}

irr::IrrlichtDevice *Device = InitDevice();

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

void binaryDataExample() {
    GameDataSerializer serializer;

    Test test; //serializable
    serializer.save("test", test);

    //load and creating PTR
    auto loaded = serializer.load<Test>("test");
    loaded->dump();

    //Or Create object and fill it
    Test filled;
    serializer.load("test", filled);
    filled.dump();
}

void mapExample() {
    GameDataSerializer serializer;
    GameMapFactory factory(serializer);

    auto map = factory.loadByTemplate("1");

    serializer.save("map1saved", *map);
}

int main() {
    srand(time(NULL));
    /*if (true) {
        mapExample();
        return 0;
    }*/
    try {
        BomberWave game;
        game.Launch();
    }
    catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
        return 84;
    }
    Device->drop();
}