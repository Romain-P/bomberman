//
// Created by Mardel on 28/05/18.
//

#ifndef CPP_INDIE_STUDIO_GAMEMANAGER_HPP
#define CPP_INDIE_STUDIO_GAMEMANAGER_HPP

#include <vector>
#include <memory>
#include "GameRenderer.hpp"
#include "GameMap.hpp"
#include "Player.hpp"
#include "GameTime.hpp"

class GameManager
{
public:
    GameManager();
    ~GameManager();
    virtual void LaunchGame() = 0;
    void SpawnObject(GameObject *object);
    const GameMap &getMap() { return _map; }
    virtual float getDeltaTime() = 0;
    int GenerateId();
    std::vector<GameObject *> getObjectsAtPosition(vector2df position);
protected:
    virtual void Cleanup() = 0;
    virtual void SpawnMapObjects() = 0;
    virtual void RunUpdates() = 0;
    virtual void RenderGame() = 0;
    bool _gameRunning;
    GameMap _map;
    std::vector<std::unique_ptr<GameObject>> _objects;
    int _currentId;
};

class SoloGameManager : public GameManager
{
public:
    SoloGameManager(int level, irr::IrrlichtDevice * const device);
    Player &getPlayer() { return _player; }
    void LaunchGame();
    float getDeltaTime();
    irr::IrrlichtDevice *const &getDevice() { return _device; }
private:
    void Cleanup();
    void SpawnMapObjects();
    void RunUpdates();
    void RenderGame();
    GameTime _time;
    irr::IrrlichtDevice * const _device;
    SoloPlayer _player;
    GameRenderer _renderer;
};

class NetWorkGameManager : public GameManager
{
public:
    NetWorkGameManager(int level);
private:
};

#endif //CPP_INDIE_STUDIO_GAMEMANAGER_HPP
