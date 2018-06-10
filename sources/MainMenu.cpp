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

    guienv->addImage(_device->getVideoDriver()->getTexture("resources/ui/MainMenuBackground.jpg"), position2d<int>(0, 0));
    guienv->addImage(_device->getVideoDriver()->getTexture("resources/ui/MainMenuText.png"), position2d<int>(750, 430));
    curr = guienv->addButton(rect<s32>(750, 430, 750 + 400, 430 + 80), nullptr, (int)MAINMENUCHOICE::SOLO,
			L"", L"Play solo");
    curr->setDrawBorder(false);
	curr = guienv->addButton(rect<s32>(830, 520, 830 + 200, 520 + 80), nullptr, (int)MAINMENUCHOICE::HOSTMULTIPLAYER,
                        L"", L"Host a local multiplayer game");
    curr->setDrawBorder(false);
    curr = guienv->addButton(rect<s32>(830, 620, 830 + 200, 620 + 80), nullptr, (int)MAINMENUCHOICE::JOINMULTIPLAYER,
			L"", L"Join a local multiplayer game");
    curr->setDrawBorder(false);
    curr = guienv->addButton(rect<s32>(830, 720, 830 + 200, 720 + 80), nullptr, (int)MAINMENUCHOICE::QUIT,
            L"", L"Quits the game");
    curr->setDrawBorder(false);
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