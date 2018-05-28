//
// Created by Mardel on 23/05/18.
//

#include "MainMenu.hpp"
#include <irrlicht.h>

MainMenu::MainMenu()
{
    guienv = irrlichtDevice->getGUIEnvironment();
}

void MainMenu::Run()
{

}

void MainMenu::Draw()
{
    guienv->drawAll();
}

