//
// Created by Mardel on 09/06/18.
//

#ifndef CPP_INDIE_STUDIO_GAMEUIMANAGER_HPP
#define CPP_INDIE_STUDIO_GAMEUIMANAGER_HPP

#include "GameManager.hpp"

class SoloGameUIManager
{
public:
    SoloGameUIManager(GameManager &manager);
    void UpdateUI();
private:
    GameManager &_manager;
};

class MultiPlayerUIManager
{
public:
    MultiPlayerUIManager(NetworkGameManager &manager);
    void UpdateUI();
private:
    NetworkGameManager &_manager;
};

#endif //CPP_INDIE_STUDIO_GAMEUIMANAGER_HPP
