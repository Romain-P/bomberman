//
// Created by Mardel on 28/05/18.
//

#include "GameManager.hpp"
#include <iostream>
#include <Walls.hpp>
#include <GameMapFactory.h>

GameManager::GameManager() : _gameRunning(false), _map(), _currentId(0) {

}

GameManager::~GameManager() {

}

void SoloGameManager::SpawnMapObjects()
{
    for (int y = 0; y < GameMap::MapSize; y++)
    {
        for (int x = 0; x < GameMap::MapSize; x++)
        {
            int spot = _map->getMapPosition(x, y);
            if (spot == 1)
            {
                SpawnObject(new SoloWall(*this, vector2df(x, y)));
            }
            else if (spot == 2)
            {
                SpawnObject(new SoloDestroyableWall(*this, vector2df(x, y)));
            }
        }
    }
}

SoloGameManager::SoloGameManager(int level, irr::IrrlichtDevice * const device) :
        GameManager(), _time(device), _device(device), _player(*this),_renderer(device)
{
    GameDataSerializer serializer;
    GameMapFactory factory(serializer);

    _map = factory.loadByTemplate(std::to_string(level));
}

void SoloGameManager::LaunchGame()
{
    _gameRunning = true;

    SpawnMapObjects();
    _player.Start();
    _time.Reset();
    while (_gameRunning && _device->run() && !_player.shouldBeDestroyed())
    {
        Cleanup();
        RunUpdates();
        RenderGame();
    }
}

void SoloGameManager::Cleanup()
{
    for (auto it = _objects.begin(); it != _objects.end();)
    {
        if ((*it)->shouldBeDestroyed())
            it = _objects.erase(it);
        else
            ++it;
    }
}

void SoloGameManager::RunUpdates()
{
    _time.Update();
    _player.Update();
    for (auto it = _objects.begin(); it != _objects.end(); it++)
    {
        (*it)->Update();
    }
}

float SoloGameManager::getDeltaTime()
{
    return _time.getDeltaTime();
}

void SoloGameManager::RenderGame()
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
