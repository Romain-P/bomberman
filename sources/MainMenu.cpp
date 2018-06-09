//
// Created by Mardel on 23/05/18.
//

#include "MainMenu.hpp"
#include <irrlicht.h>
#include <iostream>

using namespace irr;

using namespace core;
using namespace gui;
using namespace video;

MainMenu::MainMenu(irr::IrrlichtDevice * const device) : _device(device), _currentMenuChoice(MAINMENUCHOICE::NONE), _eventReceiver(_currentMenuChoice)
{
}

MAINMENUCHOICE MainMenu::Run()
{
    CreateMenu();
    _currentMenuChoice = MAINMENUCHOICE::NONE;
    _device->setEventReceiver(&_eventReceiver);
    while (_device->run())
    {
        if (_device->isWindowActive())
        {
            _device->getVideoDriver()->beginScene(true, true, SColor(0, 200, 200, 200));
            Draw();
            if (_currentMenuChoice != MAINMENUCHOICE::NONE)
                return _currentMenuChoice;
            _device->getVideoDriver()->endScene();
        }
    }
    return  MAINMENUCHOICE::NONE;
}

void MainMenu::CreateMenu()
{
    IGUIButton *curr;
    irr::gui::IGUIEnvironment *guienv = _device->getGUIEnvironment();

    curr = guienv->addButton(rect<s32>(860, 240, 860 + 200, 240 + 100), nullptr, (int)MAINMENUCHOICE::SOLO,
			L"Adventure", L"Play solo");
    curr->setUseAlphaChannel(true);
	guienv->addButton(rect<s32>(860, 360, 860 + 200, 360 + 100), nullptr, (int)MAINMENUCHOICE::JOINMULTIPLAYER,
                        L"Join Game", L"Join a local multiplayer game");
	guienv->addButton(rect<s32>(860, 480, 860 + 200, 480 + 100), nullptr, (int)MAINMENUCHOICE::HOSTMULTIPLAYER,
			L"Host Game", L"Host a local multiplayer game");
	guienv->addButton(rect<s32>(860, 600, 860 + 200, 600 + 100), nullptr, (int)MAINMENUCHOICE::QUIT,
            L"Quit", L"Quits the game");
}

void MainMenu::Draw()
{
    _device->getGUIEnvironment()->drawAll();
}

MainMenuEventReceiver::MainMenuEventReceiver(MAINMENUCHOICE &menuChoice) : _menuChoice(menuChoice)
{

}

bool MainMenuEventReceiver::OnEvent(const irr::SEvent &event)
{
    if (event.EventType == EET_GUI_EVENT)
    {
        s32 id = event.GUIEvent.Caller->getID();
        switch(event.GUIEvent.EventType)
        {
            case EGET_BUTTON_CLICKED:
                switch((MAINMENUCHOICE)id)
                {
                    case MAINMENUCHOICE::SOLO :
                        _menuChoice = MAINMENUCHOICE::SOLO;
                        break;
                    case MAINMENUCHOICE::JOINMULTIPLAYER :
                        _menuChoice = MAINMENUCHOICE::JOINMULTIPLAYER;
                        break;
                    case MAINMENUCHOICE::HOSTMULTIPLAYER :
                        _menuChoice = MAINMENUCHOICE::HOSTMULTIPLAYER;
                        break;
                    case MAINMENUCHOICE::QUIT :
                        _menuChoice = MAINMENUCHOICE::QUIT;
                        break;
                    default :
                        _menuChoice = MAINMENUCHOICE::NONE;
                        break;
                }
                break;
            default:
                break;
        }
    }
    return false;
}