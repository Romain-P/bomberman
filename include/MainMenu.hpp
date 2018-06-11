//
// Created by Mardel on 23/05/18.
//

#ifndef CPP_INDIE_STUDIO_MAINMENU_HPP
#define CPP_INDIE_STUDIO_MAINMENU_HPP

#include <irrlicht.h>
#include <memory>

using namespace irr;

using namespace core;
using namespace gui;

enum class MAINMENUCHOICE
{
    NONE = 101,
    SOLO,
    JOINMULTIPLAYER,
    HOSTMULTIPLAYER,
    QUIT,
    DUO,
    BACK
};

class MainMenuEventReceiver : public irr::IEventReceiver
{
public:
    MainMenuEventReceiver(MAINMENUCHOICE &menuChoice);
    virtual bool OnEvent(const irr::SEvent &event);
private:
    MAINMENUCHOICE &_menuChoice;
};

class MainMenu
{
public:
    MainMenu(irr::IrrlichtDevice * const device);
    MAINMENUCHOICE Run();
    MAINMENUCHOICE RunAdventure();
    void CreateAdventureMenu();
    void CreateMenu();
private:
    void Draw();
    irr::IrrlichtDevice * const _device;
    MAINMENUCHOICE _currentMenuChoice;
    MainMenuEventReceiver _eventReceiver;
};

#endif //CPP_INDIE_STUDIO_MAINMENU_HPP
