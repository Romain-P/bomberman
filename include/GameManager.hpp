//
// Created by Mardel on 28/05/18.
//

#ifndef CPP_INDIE_STUDIO_GAMEMANAGER_HPP
#define CPP_INDIE_STUDIO_GAMEMANAGER_HPP

class NetworkGameManager;

#include <vector>
#include <memory>
#include "GameRenderer.hpp"
#include "GameMap.hpp"
#include "Player.hpp"
#include "GameTime.hpp"
#include "BackgroundLoader.hpp"
#include "GameSession.h"
#include "GameUIManager.hpp"
#include "GameSessionController.h"
#include <map>
#include <thread>

enum class GAMETYPE
{
    SOLO,
    DUO,
    PVP
};
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
    explicit GameManager(GAMETYPE gameType);
    ~GameManager();
    virtual void LaunchGame();
    void SpawnObject(GameObject *object);
    void setMap(GameMap &map) { _map = std::unique_ptr<GameMap>(new GameMap(map.getData(), map.getCompletionTime()));}
    const GameMap &getMap() { return *_map; }
    std::map<int, std::unique_ptr<Player>>  &getPlayers() { return _players; }
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
    void LaunchLevel();
    void LoadMap();
    void Cleanup();
    void SpawnMapObjects();
    virtual void RunUpdates();
    void RenderGame();
    GameTime _time;
    GameRenderer _renderer;
    std::unique_ptr<IEventReceiver> _eventReceiver;
    std::map<int, std::unique_ptr<Player>> _players;
    bool _gameRunning;
    std::unique_ptr<GameUIManager> _uiManager;
    std::unique_ptr<GameMap> _map;
    std::vector<std::unique_ptr<GameObject>> _objects;
    int _currentId;
    int _score;
    BackgroundLoader _bgLoader;
    int _level;
    bool _gameWon;
};

class NetworkGameManager : public GameManager
{
public:
    explicit NetworkGameManager(GameSessionController &controller, GameSession *session);
    void LaunchGame();
    void Run();
    bool Update();
    void setLocalPlayerNbr(int nbr) { _localPlayerNbr = nbr; }
private:
    void RunUpdates();
    GameSessionController &_controller;
    GameSession *_session;
    int _localPlayerNbr;
};

class GameEventReceiver : public irr::IEventReceiver
{
public:
    GameEventReceiver(std::array<bool, 6> &inputs);
    virtual bool OnEvent(const irr::SEvent &event);
private:
    std::array<bool, 6> &_inputs;
};

class NetworkGameEventReceiver : public irr::IEventReceiver
{
public:
    NetworkGameEventReceiver(std::array<bool, 6> &inputs, GameSession *session);
    virtual bool OnEvent(const irr::SEvent &event);
private:
    std::array<bool, 6> &_inputs;
    GameSession *_session;
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

#endif //CPP_INDIE_STUDIO_GAMEMANAGER_HPP
