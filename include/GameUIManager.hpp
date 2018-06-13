//
// Created by Mardel on 09/06/18.
//

#ifndef CPP_INDIE_STUDIO_GAMEUIMANAGER_HPP
#define CPP_INDIE_STUDIO_GAMEUIMANAGER_HPP

#include "GameManager.hpp"

class GameUIManager
{
public:
    GameUIManager(GameManager &manager);
    virtual void UpdateUI();
private:
    GameManager &_manager;
};

class NetworkGameUIManager : public GameUIManager
{
public:
    NetworkGameUIManager(GameManager &manager, int playerNbr);
    void UpdateUI();
private:
    int _playerNbr;
};

#endif //CPP_INDIE_STUDIO_GAMEUIMANAGER_HPP
