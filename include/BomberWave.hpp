//
// Created by Mardel on 23/05/18.
//

#ifndef CPP_INDIE_STUDIO_BOMBERWAVE_HPP
#define CPP_INDIE_STUDIO_BOMBERWAVE_HPP

#include <memory>
#include "../include/MainMenu.hpp"
#include <irrlicht.h>

using namespace irr;

extern std::unique_ptr<irr::IrrlichtDevice> irrlichtDevice;

class BomberWave
{
public:
    enum MENUCHOICE
    {
        NULL,
        SOLO,
        MULTIPLAYER
    };

    BomberWave();
private:
    MainMenu _mainMenu;
};

#endif //CPP_INDIE_STUDIO_BOMBERWAVE_HPP
