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
    std::vector<std::unique_ptr<Player>> &players = _manager.getPlayers();
    int x = 180;
    int y = 0;
    for (auto it = players.begin(); it != players.end(); it++)
    {
        std::string iconPath = "resources/ui/" + (*it)->getCharacterColor() + "BombermanIcon.png";
        std::wstring wiconPath = std::wstring(iconPath.begin(), iconPath.end());
        guienv->addImage(_manager.getDevice()->getVideoDriver()->getTexture(wiconPath.c_str()),
                         position2d<int>(20, y + 20));
        std::vector<std::unique_ptr<PlayerBuff>> &buffs = (*it)->getBuffs();
        for (auto it = buffs.begin(); it != buffs.end(); it++)
        {
            iconPath = (*it)->getIcon();
            std::wstring wiconPath = std::wstring(iconPath.begin(), iconPath.end());
            guienv->addImage(_manager.getDevice()->getVideoDriver()->getTexture(wiconPath.c_str()),
                             position2d<int>(x, y + 50));
            x += 80;
        }
        x = 180;
        y += 200;
    }
}

MultiPlayerUIManager::MultiPlayerUIManager(NetworkGameManager &manager) : _manager(manager)
{

}

void MultiPlayerUIManager::UpdateUI()
{

}
