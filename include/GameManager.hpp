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
#include "BackgroundLoader.hpp"

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
    explicit GameManager(bool duo = false);
    ~GameManager();
    void LaunchGame();
    void SpawnObject(GameObject *object);
    const GameMap &getMap() { return *_map; }
    std::vector<std::unique_ptr<Player>> &getPlayers() { return _players; }
    float getDeltaTime();
    int GenerateId();
    bool GameOver();
    void RemoveDestroyed();
    void IncreaseScore(int increment) { _players[0]->IncreaseScore(increment); }
    int getScore() { return _players[0]->getScore(); }
    void Win();
    std::vector<GameObject *> getObjectsAtPosition(vector2df position);
    std::vector<GameObject *> getCollisionsWithTags(GameObject &object, std::vector<GOTAG> &tags);
protected:
    virtual void LaunchLevel();
    virtual void LoadMap();
    virtual void Cleanup();
    virtual void SpawnMapObjects();
    virtual void RunUpdates();
    virtual void RenderGame();
    GameTime _time;
    GameRenderer _renderer;
    std::unique_ptr<IEventReceiver> _eventReceiver;
    std::vector<std::unique_ptr<Player>> _players;
    bool _gameRunning;
    std::unique_ptr<GameMap> _map;
    std::vector<std::unique_ptr<GameObject>> _objects;
    int _currentId;
    int _score;
    BackgroundLoader _bgLoader;
    int _level;
    bool _gameWon;
};

class GameEventReceiver : public irr::IEventReceiver
{
public:
    GameEventReceiver(std::array<bool, 6> &inputs);
    virtual bool OnEvent(const irr::SEvent &event);
private:
    std::array<bool, 6> &_inputs;
};

class DuoGameEventReceiver : public irr::IEventReceiver
{
public:
    DuoGameEventReceiver(std::array<bool, 6> &inputs, std::array<bool, 6> &inputstwo);
    virtual bool OnEvent(const irr::SEvent &event);
private:
    std::array<bool, 6> &_inputs;
    std::array<bool, 6> &_inputstwo;
};
/*
class NetworkGameManager : public GameManager
{
public:
    NetworkGameManager(irr::IrrlichtDevice * const device);
    void LaunchGame() {};
    void JoinServer(uint16_t port);
protected:
    void Cleanup() {};
    void RunUpdates() {};
    void RenderGame() {};
    std::vector<std::pair<int, Player>> _enemyPlayers;
};*/

#endif //CPP_INDIE_STUDIO_GAMEMANAGER_HPP
