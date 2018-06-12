//
// Created by Mardel on 23/05/18.
//

#include "MainMenu.hpp"
#include <irrlicht.h>
#include <iostream>
#include <BomberWave.hpp>

using namespace irr;

using namespace core;
using namespace gui;
using namespace video;

MainMenu::MainMenu() : _currentMenuChoice(MAINMENUCHOICE::NONE), _eventReceiver(_currentMenuChoice)
{
}

MAINMENUCHOICE MainMenu::Run()
{
    CreateMenu();
    _currentMenuChoice = MAINMENUCHOICE::NONE;
    Device->setEventReceiver(&_eventReceiver);
    while (Device->run())
    {
        if (Device->isWindowActive())
        {
            Device->getVideoDriver()->beginScene(true, true, SColor(0, 200, 200, 200));
            Draw();
            if (_currentMenuChoice != MAINMENUCHOICE::NONE)
                return _currentMenuChoice;
            Device->getVideoDriver()->endScene();
        }
    }
    return  MAINMENUCHOICE::NONE;
}

MAINMENUCHOICE MainMenu::RunAdventure()
{
    CreateAdventureMenu();
    _currentMenuChoice = MAINMENUCHOICE::NONE;
    Device->setEventReceiver(&_eventReceiver);
    while (Device->run())
    {
        if (Device->isWindowActive())
        {
            Device->getVideoDriver()->beginScene(true, true, SColor(0, 200, 200, 200));
            Draw();
            if (_currentMenuChoice != MAINMENUCHOICE::NONE)
            {
                return _currentMenuChoice;
            }
            Device->getVideoDriver()->endScene();
        }
    }
    return  MAINMENUCHOICE::NONE;
}

void MainMenu::CreateMenu()
{
    IGUIButton *curr;
    irr::gui::IGUIEnvironment *guienv = Device->getGUIEnvironment();

    guienv->addImage(Device->getVideoDriver()->getTexture("resources/ui/MainMenuBackground.jpg"), position2d<int>(0, 0));
    guienv->addImage(Device->getVideoDriver()->getTexture("resources/ui/MainMenuText.png"), position2d<int>(750, 430));
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


void MainMenu::CreateAdventureMenu()
{
    IGUIButton *curr;
    irr::gui::IGUIEnvironment *guienv = Device->getGUIEnvironment();

    guienv->addImage(Device->getVideoDriver()->getTexture("resources/ui/MainMenuBackground.jpg"), position2d<int>(0, 0));
    guienv->addImage(Device->getVideoDriver()->getTexture("resources/ui/AdventureMenuText.png"), position2d<int>(850, 430));
    curr = guienv->addButton(rect<s32>(830, 430, 750 + 400, 430 + 80), nullptr, (int)MAINMENUCHOICE::SOLO,
                             L"", L"Play solo");
    curr->setDrawBorder(false);
    curr = guienv->addButton(rect<s32>(830, 520, 830 + 200, 520 + 60), nullptr, (int)MAINMENUCHOICE::DUO,
                             L"", L"Play duo");
    curr->setDrawBorder(false);
    curr = guienv->addButton(rect<s32>(830, 600, 830 + 200, 620 + 80), nullptr, (int)MAINMENUCHOICE::BACK,
                             L"", L"Return to main menu");
    curr->setDrawBorder(false);
}

void MainMenu::Draw()
{
    Device->getGUIEnvironment()->drawAll();
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
                    case MAINMENUCHOICE::DUO:
                        _menuChoice = MAINMENUCHOICE ::DUO;
                        break;
                    case MAINMENUCHOICE::BACK:
                        _menuChoice = MAINMENUCHOICE ::BACK;
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