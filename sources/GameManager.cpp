//
// Created by Mardel on 28/05/18.
//

#include "GameManager.hpp"
#include <iostream>
#include <Walls.hpp>
#include <GameMapFactory.h>
#include <thread>
#include <Explosion.hpp>
#include <Monster.hpp>
#include <PowerUps.hpp>
#include <GameUIManager.hpp>

GameManager::GameManager(irr::IrrlichtDevice * const device) :
        _time(device), _renderer(device), _device(device), _player(*this), _gameRunning(false), _currentId(0), _bgLoader(device)
{
}

GameManager::GameManager(int level, irr::IrrlichtDevice * const device) :
        _time(device), _renderer(device), _device(device), _player(*this), _gameRunning(false), _currentId(0), _bgLoader(device)
{
    GameDataSerializer serializer;
    GameMapFactory factory(serializer);

    _map = factory.loadByTemplate(std::to_string(level));
}

NetworkGameManager::NetworkGameManager(irr::IrrlichtDevice * const device) :
        GameManager(device)
{
}

void NetworkGameManager::JoinServer(uint16_t port)
{
    /*GameSessionConnector connector;
    std::thread con([&connector] { connector.tryConnect("127.0.0.1", port); });*/
}

NetworkHostGameManager::NetworkHostGameManager(irr::IrrlichtDevice * const device) :
        NetworkGameManager(device), _server("127.0.0.1", RANDOM_PORT)
{
}

void NetworkHostGameManager::JoinServer()
{
    /*GameSessionConnector connector;
    std::thread con([&connector] { connector.tryConnect("127.0.0.1", _server.getPort()};*/
}

void NetworkHostGameManager::LaunchServer()
{
/*    std::thread thread([&_server] {_server.start()});

    while (_server.getPort() == 0);*/
}

GameManager::~GameManager()
{

}

void GameManager::SpawnMapObjects()
{
    for (int y = 0; y < GameMap::MapSize; y++)
    {
        for (int x = 0; x < GameMap::MapSize; x++)
        {
            int spot = _map->getMapPosition(x, y);
            if (spot == 1)
            {
                SpawnObject(new Wall(*this, vector2df(x, y)));
            }
            else if (spot == 2)
            {
                SpawnObject(new DestroyableWall(*this, vector2df(x, y)));
            }
        }
    }
    for (int i = 0; i < _map->getEnemyCount(); i++)
    {
        SpawnObject(new Monster(*this, _map->getGoal()));
    }
}

void GameManager::LaunchGame()
{
    SoloGameUIManager uiManager(*this);
    _gameRunning = true;

    _bgLoader.LoadRandomBackground();
    _bgLoader.LoadRandomTerrain();
    SpawnObject(new SpeedPowerUp(*this, vector2df(1, 11)));
    SpawnObject(new BonusBombPowerUp(*this, vector2df(2, 11)));
    SpawnObject(new BombPowerPowerUp(*this, vector2df(3, 11)));
    SpawnMapObjects();
    _time.Reset();
    while (_gameRunning && _device->run() && !_player.shouldBeDestroyed())
    {
        RemoveDestroyed();
        uiManager.UpdateUI();
        RunUpdates();
        RenderGame();
    }
    Cleanup();
}

void GameManager::RemoveDestroyed()
{
    for (auto it = _objects.begin(); it != _objects.end();)
    {
        if ((*it)->shouldBeDestroyed())
            it = _objects.erase(it);
        else
            ++it;
    }
}

void GameManager::Cleanup()
{
    _device->getSceneManager()->clear();
    _device->getGUIEnvironment()->clear();
}

void GameManager::RunUpdates()
{
    _time.Update();
    _player.Update();
    for (auto it = _objects.begin(); it != _objects.end(); it++)
    {
        (*it)->Update();
    }
}

float GameManager::getDeltaTime()
{
    return _time.getDeltaTime();
}

void GameManager::RenderGame()
{
    _renderer.Render();
}

int GameManager::GenerateId()
{
    _currentId++;
    return _currentId;
}

void GameManager::SpawnObject(GameObject *object)
{
    _objects.emplace_back(std::unique_ptr<GameObject>(object));
}

std::vector<GameObject *> GameManager::getObjectsAtPosition(vector2df position)
{
    std::vector<GameObject *> objects;

    for (auto it = _objects.begin(); it != _objects.end(); it++)
    {
        if ((int)position.X == (int)(*it)->getPosition().X && (int)position.Y == (int)(*it)->getPosition().Y)
        {
            objects.push_back((*it).get());
        }
    }
    return objects;
}


std::vector<GameObject *> GameManager::getCollisionsWithTags(GameObject &object, std::vector<GOTAG> &tags)
{
    std::vector<GameObject *> objects;

    for (auto it = _objects.begin(); it != _objects.end(); it++)
    {
        if ((int)object.getPosition().X == (int)(*it)->getPosition().X && (int)object.getPosition().Y == (int)(*it)->getPosition().Y)
        {
            if (tags.empty() && (*it)->getId() != object.getId())
                objects.push_back((*it).get());
            else
            {
                for (auto tagsIt = tags.begin(); tagsIt != tags.end(); tagsIt++)
                {
                    if (object.getId() != (*it)->getId() && (*it)->HasTag(*tagsIt))
                    {
                        objects.push_back((*it).get());
                        break;
                    }
                }
            }
        }
    }
    return objects;
}