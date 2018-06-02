//
// Created by Mardel on 28/05/18.
//

#include "GameManager.hpp"

GameManager::GameManager(int level, irr::IrrlichtDevice * const device) :  _gameRunning(false), _device(device), _map(level), _player(*this), _time(device)
{

}

void GameManager::LaunchGame()
{
    _gameRunning = true;

    _player.Start();
    while (_gameRunning)
    {
        RunUpdates();
    }
}

void GameManager::RunUpdates()
{
    _player.Update();
    for (auto it = _objects.begin(); it != _objects.end(); it++)
        it->Update();
}

void GameManager::SpawnObject(GameObject object)
{
    _objects.push_back(std::move(object));

}

float GameManager::getDeltaTime()
{
    return _time.getDeltaTime();
}

int GameManager::GenerateId()
{
    _currentId++;
    return _currentId;
}

void GameManager::RenderMap()
{

}

void GameManager::RenderObjects()
{

}

void GameManager::RenderUI() {

}
