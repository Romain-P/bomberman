//
// Created by Mardel on 23/05/18.
//

#ifndef CPP_INDIE_STUDIO_BOMBERWAVE_HPP
#define CPP_INDIE_STUDIO_BOMBERWAVE_HPP

#include <memory>
#include "MainMenu.hpp"
#include "GameTime.hpp"
#include <irrlicht.h>

class BomberWave
{
public:
    BomberWave();
    void Launch();
    static GameTime Time;
private:
    irr::IrrlichtDevice *InitDevice();
    void LaunchMainMenu();
    void LaunchSolo();
    void LaunchMultiplayerHost();
    void LaunchMultiplayerJoin();
    irr::IrrlichtDevice * const _device;
    MainMenu _mainMenu;
    bool _gameRunning;
};

#endif //CPP_INDIE_STUDIO_BOMBERWAVE_HPP
