//
// Created by Mardel on 09/06/18.
//

#include "GameUIManager.hpp"

SoloGameUIManager::SoloGameUIManager(GameManager &manager) : _manager(manager)
{

}

void SoloGameUIManager::UpdateUI()
{
    irr::gui::IGUIEnvironment *guienv = _manager.getDevice()->getGUIEnvironment();
    guienv->clear();
    std::string sscore = std::to_string(_manager.getScore());
    std::wstring wscore = std::wstring(sscore.begin(), sscore.end());
    guienv->addStaticText(wscore.c_str(), rect<s32>(1920 / 2 - 50, 20, 1920 / 2 + 50, 40));

    MainPlayer &player = _manager.getPlayer();
    std::string iconPath = "resources/ui/" + player.getCharacterColor() + "BombermanIcon.png";
    std::wstring wiconPath = std::wstring(iconPath.begin(), iconPath.end());
    guienv->addImage(_manager.getDevice()->getVideoDriver()->getTexture(wiconPath.c_str()), position2d<int>(20, 20));
    std::vector<std::unique_ptr<PlayerBuff>> &buffs = player.getBuffs();
    int x = 180;
    int y = 50;
    for (auto it = buffs.begin(); it != buffs.end(); it++)
    {
        iconPath = (*it)->getIcon();
        std::wstring wiconPath = std::wstring(iconPath.begin(), iconPath.end());
        guienv->addImage(_manager.getDevice()->getVideoDriver()->getTexture(wiconPath.c_str()), position2d<int>(x, y));
        x += 80;
    }
}

MultiPlayerUIManager::MultiPlayerUIManager(NetworkGameManager &manager) : _manager(manager)
{

}

void MultiPlayerUIManager::UpdateUI()
{

}
