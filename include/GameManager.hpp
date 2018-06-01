//
// Created by Mardel on 28/05/18.
//

#ifndef CPP_INDIE_STUDIO_GAMEMANAGER_HPP
#define CPP_INDIE_STUDIO_GAMEMANAGER_HPP

class GameManager;

#include <vector>
#include "GameRenderer.hpp"
#include "GameMap.hpp"
#include "Player.hpp"

class GameManager
{
public:
    GameManager(int level);
    void LaunchGame();
    void SpawnObject(GameObject object);
    const GameMap &getMap() { return _map; }
    Player &getPlayer() { return _player; }
    virtual void RenderMap();
    virtual void RenderObjects();
    int GenerateId();
protected:
    void RunUpdates();
    bool _gameRunning;
    GameMap _map;
    std::vector<GameObject> _objects;
    int _currentId;
private:
    Player _player;
    GameRenderer _renderer;

};

class NetWorkGameManager : public GameManager
{
public:
    NetWorkGameManager(int level);
    void RenderMap();
    void RenderObjects();
private:
};

#endif //CPP_INDIE_STUDIO_GAMEMANAGER_HPP
