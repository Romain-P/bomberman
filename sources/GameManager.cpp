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

GameManager::GameManager(irr::IrrlichtDevice * const device, bool duo) :
        _time(device), _renderer(device), _device(device), _gameRunning(false), _currentId(0), _bgLoader(device), _level(1), _gameWon(false)
{
    _players.push_back(std::unique_ptr<Player>(new Player(*this, 0)));
    if (duo)
    {
        _players.push_back(std::unique_ptr<Player>(new Player(*this, 1)));
        _eventReceiver = std::make_unique<DuoGameEventReceiver>(_players[0]->getInputs(), _players[1]->getInputs());
    }
    else
        _eventReceiver = std::make_unique<GameEventReceiver>(_players[0]->getInputs());
    _device->setEventReceiver(_eventReceiver.get());
}

NetworkGameManager::NetworkGameManager(irr::IrrlichtDevice * const device) :
        GameManager(device)
{
}

void GameManager::LoadMap()
{
    GameDataSerializer serializer;
    GameMapFactory factory(serializer);

    _map = factory.loadByTemplate(std::to_string(_level));
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
    GameSessionConnector connector;
    std::thread con([&connector] { connector.tryConnect("127.0.0.1", _server.getPort()); });
}

void NetworkHostGameManager::LaunchServer()
{
    std::thread thread([&_server] {_server.start()});

    while (_server.getPort() == 0);
    JoinServer();
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
            if (spot == GameMap::CellType::WALL)
            {
                SpawnObject(new Wall(*this, vector2df(x, y)));
            }
            else if (spot == GameMap::CellType::BREAKABLE_WALL)
            {
                SpawnObject(new DestroyableWall(*this, vector2df(x, y)));
            }
            else if (spot == GameMap::CellType::ENEMY_SPAWN)
            {
                SpawnObject(new Goal(*this, vector2df(x, y)));
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
    while (_level < 3)
    {
        LaunchLevel();
        _level++;
        if (!_gameWon)
            return;
        _gameWon = false;
    }
    _device->getSceneManager()->clear();
}

void GameManager::Win()
{
    _gameWon = true;
}

void GameManager::LaunchLevel()
{
    SoloGameUIManager uiManager(*this);
    _gameRunning = true;
    LoadMap();
    _bgLoader.LoadRandomBackground();
    _bgLoader.LoadRandomTerrain();
    for (auto it = _players.begin(); it != _players.end(); it++)
        (*it)->setPosition(_map->getPlayerSpawns()[0]);
    SpawnMapObjects();
    _time.Reset();
    while (_gameRunning && _device->run() && !GameOver() & !_gameWon)
    {
        RemoveDestroyed();
        uiManager.UpdateUI();
        RunUpdates();
        RenderGame();
    }
    Cleanup();
}

bool GameManager::GameOver()
{
    for (auto it = _players.begin(); it != _players.end(); it++)
    {
        if (!(*it)->shouldBeDestroyed())
            return false;
    }
    return true;
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
    for (auto it = _objects.begin(); it != _objects.end(); it++)
    {
        (*it)->Destroy();
    }
    _device->getGUIEnvironment()->clear();
}

void GameManager::RunUpdates()
{
    _time.Update();
    for (auto it = _players.begin(); it != _players.end(); it++)
    {
        if (!(*it)->shouldBeDestroyed())
            (*it)->Update();
    }
    for (auto it = _objects.begin(); it != _objects.end(); it++)
    {
        if (!(*it)->shouldBeDestroyed())
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

GameEventReceiver::GameEventReceiver(std::array<bool, 6> &inputs) : _inputs(inputs)
{

}

bool GameEventReceiver::OnEvent(const irr::SEvent &event)
{
    if (event.EventType == irr::EET_KEY_INPUT_EVENT)
    {
        switch(event.KeyInput.Key)
        {
            case KEY_ESCAPE:
                _inputs[(int)PLAYERINPUT::PAUSE] = event.KeyInput.PressedDown;
                break;
            case KEY_SPACE:
                _inputs[(int)PLAYERINPUT::PLACEBOMB] = event.KeyInput.PressedDown;
                break;
            case KEY_UP:
            case KEY_KEY_Z:
                _inputs[(int)PLAYERINPUT::UP] = event.KeyInput.PressedDown;
                break;
            case KEY_DOWN:
            case KEY_KEY_S:
                _inputs[(int)PLAYERINPUT::DOWN] = event.KeyInput.PressedDown;
                break;
            case KEY_LEFT:
            case KEY_KEY_Q:
                _inputs[(int)PLAYERINPUT::LEFT] = event.KeyInput.PressedDown;
                break;
            case KEY_RIGHT:
            case KEY_KEY_D:
                _inputs[(int)PLAYERINPUT::RIGHT] = event.KeyInput.PressedDown;
                break;
            default:
                break;
        }
    }
    return false;
}

DuoGameEventReceiver::DuoGameEventReceiver(std::array<bool, 6> &inputs,std::array<bool, 6> &inputstwo) : _inputs(inputs), _inputstwo(inputstwo)
{

}

bool DuoGameEventReceiver::OnEvent(const irr::SEvent &event)
{
    if (event.EventType == irr::EET_KEY_INPUT_EVENT)
    {
        switch(event.KeyInput.Key)
        {
            case KEY_ESCAPE:
                _inputs[(int)PLAYERINPUT::PAUSE] = event.KeyInput.PressedDown;
                break;
            case KEY_SPACE:
                _inputs[(int)PLAYERINPUT::PLACEBOMB] = event.KeyInput.PressedDown;
                break;
            case KEY_END:
                _inputstwo[(int)PLAYERINPUT::PLACEBOMB] = event.KeyInput.PressedDown;
                break;
            case KEY_UP:
                _inputstwo[(int)PLAYERINPUT::UP] = event.KeyInput.PressedDown;
                break;
            case KEY_KEY_Z:
                _inputs[(int)PLAYERINPUT::UP] = event.KeyInput.PressedDown;
                break;
            case KEY_DOWN:
                _inputstwo[(int)PLAYERINPUT::DOWN] = event.KeyInput.PressedDown;
                break;
            case KEY_KEY_S:
                _inputs[(int)PLAYERINPUT::DOWN] = event.KeyInput.PressedDown;
                break;
            case KEY_LEFT:
                _inputstwo[(int)PLAYERINPUT::LEFT] = event.KeyInput.PressedDown;
                break;
            case KEY_KEY_Q:
                _inputs[(int)PLAYERINPUT::LEFT] = event.KeyInput.PressedDown;
                break;
            case KEY_RIGHT:
                _inputstwo[(int)PLAYERINPUT::RIGHT] = event.KeyInput.PressedDown;
                break;
            case KEY_KEY_D:
                _inputs[(int)PLAYERINPUT::RIGHT] = event.KeyInput.PressedDown;
                break;
            default:
                break;
        }
    }
    return false;
}