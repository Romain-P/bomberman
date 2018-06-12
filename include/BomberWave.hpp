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
extern irr::IrrlichtDevice *Device;

class BomberWave
{
public:
    BomberWave();
    void Launch();
private:
    void LaunchMainMenu();
    void LaunchSolo();
    void LaunchMultiplayerHost();
    void LaunchMultiplayerJoin();
    MainMenu _mainMenu;
    bool _gameRunning = false;
};

#endif //CPP_INDIE_STUDIO_BOMBERWAVE_HPP
