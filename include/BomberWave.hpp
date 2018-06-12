//
// Created by Mardel on 23/05/18.
//

#ifndef CPP_INDIE_STUDIO_BOMBERWAVE_HPP
#define CPP_INDIE_STUDIO_BOMBERWAVE_HPP

#include <memory>
#include "MainMenu.hpp"
#include "GameTime.hpp"
#include "GameServer.h"
#include "GameSessionConnector.h"
#include <irrlicht.h>
#include <irrKlang.h>

extern irrklang::ISoundEngine *SoundEngine;

class BomberWave
{
public:
    BomberWave();
    void Launch();
private:
    irr::IrrlichtDevice *InitDevice();
    void LaunchMainMenu();
    void LaunchSolo();
    void LaunchMultiplayerHost();
    void LaunchMultiplayerJoin();
    irr::IrrlichtDevice * const _device;
    MainMenu _mainMenu;
    bool _gameRunning = false;
};

#endif //CPP_INDIE_STUDIO_BOMBERWAVE_HPP
