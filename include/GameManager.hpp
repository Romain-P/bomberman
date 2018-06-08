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
#include "GameSessionConnector.h"
#include "GameServer.h"

enum class PLAYERCOLOR
{
    WHITE,
    RED,
    BLACK,
    BLUE
};

class GameManager
{
public:
    GameManager(irr::IrrlichtDevice * const device);
    GameManager(int level,  irr::IrrlichtDevice * const device);
    ~GameManager();
    void LaunchGame();
    void SpawnObject(GameObject *object);
    const GameMap &getMap() { return *_map; }
    irr::IrrlichtDevice *const &getDevice() { return _device; }
    float getDeltaTime();
    int GenerateId();
    void RemoveDestroyed();
    std::vector<GameObject *> getObjectsAtPosition(vector2df position);
    std::vector<GameObject *> getCollisionsWithTags(GameObject &object, std::vector<GOTAG> &tags);
protected:
    virtual void Cleanup();
    virtual void SpawnMapObjects();
    virtual void RunUpdates();
    virtual void RenderGame();
    GameTime _time;
    GameRenderer _renderer;
    irr::IrrlichtDevice * const _device;
    MainPlayer _player;
    bool _gameRunning;
    std::unique_ptr<GameMap> _map;
    std::vector<std::unique_ptr<GameObject>> _objects;
    int _currentId;
};

class NetworkGameManager : public GameManager
{
public:
    NetworkGameManager(irr::IrrlichtDevice * const device);
    Player &getPlayer() { return _player; }
    void LaunchGame() {};
    void JoinServer(uint16_t port);
protected:
    void Cleanup() {};
    void RunUpdates() {};
    void RenderGame() {};
    std::vector<std::pair<int, Player>> _enemyPlayers;
    GameSessionConnector _connector;
};

class NetworkHostGameManager : public NetworkGameManager
{
public:
    NetworkHostGameManager(irr::IrrlichtDevice * const device);
    void LaunchServer();
    void JoinServer();
private:
    GameServer _server;
};

#endif //CPP_INDIE_STUDIO_GAMEMANAGER_HPP
