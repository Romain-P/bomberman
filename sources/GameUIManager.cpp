//
// Created by Mardel on 09/06/18.
//

#include <BomberWave.hpp>
#include "GameUIManager.hpp"

GameUIManager::GameUIManager(GameManager &manager) : _manager(manager)
{

}

void GameUIManager::UpdateUI()
{
    irr::gui::IGUIEnvironment *guienv = Device->getGUIEnvironment();
    guienv->clear();
    std::string sscore = std::to_string(_manager.getScore());
    std::wstring wscore = std::wstring(sscore.begin(), sscore.end());
    guienv->addStaticText(wscore.c_str(), rect<s32>(1920 / 2 - 50, 20, 1920 / 2 + 50, 40));
    std::map<int, std::unique_ptr<Player>> &players = _manager.getPlayers();
    int x = 180;
    int y = 0;
    for (auto it = players.begin(); it != players.end(); it++)
    {
        if (!it->second->shouldBeDestroyed())
        {
            std::string iconPath = "resources/ui/" + it->second->getCharacterColor() + "BombermanIcon.png";
            std::wstring wiconPath = std::wstring(iconPath.begin(), iconPath.end());
            guienv->addImage(Device->getVideoDriver()->getTexture(wiconPath.c_str()),
                             position2d<int>(20, y + 20));
            std::vector<std::unique_ptr<PlayerBuff>> &buffs = it->second->getBuffs();
            for (auto itb = buffs.begin(); itb != buffs.end(); itb++)
            {
                iconPath = (*itb)->getIcon();
                std::wstring wiconPath = std::wstring(iconPath.begin(), iconPath.end());
                guienv->addImage(Device->getVideoDriver()->getTexture(wiconPath.c_str()),
                                 position2d<int>(x, y + 50));
                x += 80;
            }
        }
        else
        {
            std::string iconPath = "resources/ui/DeadBombermanIcon.png";
            std::wstring wiconPath = std::wstring(iconPath.begin(), iconPath.end());
            guienv->addImage(Device->getVideoDriver()->getTexture(wiconPath.c_str()),
                             position2d<int>(20, y + 20));
        }
        x = 180;
        y += 200;
    }
}

NetworkGameUIManager::NetworkGameUIManager(GameManager &manager, int playerNbr) : GameUIManager(manager), _playerNbr(playerNbr)
{

}

void NetworkGameUIManager::UpdateUI() {

}
