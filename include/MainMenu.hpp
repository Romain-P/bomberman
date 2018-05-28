//
// Created by Mardel on 23/05/18.
//

#ifndef CPP_INDIE_STUDIO_MAINMENU_HPP
#define CPP_INDIE_STUDIO_MAINMENU_HPP

#include "../include/BomberWave.hpp"

class MainMenuEventReceiver : public IEventReceiver
{
public:
    MainMenuEventReceiver();
    virtual bool OnEvent(const SEvent &event);
private:
};

class MainMenu
{
public:
    MainMenu();
    irr::gui::IGUIEnvironment *guienv;
    void Run();
    void Draw();
private:
    MainMenuEventReceiver _eventReceiver;
};

#endif //CPP_INDIE_STUDIO_MAINMENU_HPP
